#include "PTRMasterNPC.h"
#include "PTRCommon.h"
#include "PTRConfig.h"
#include "PTRGearData.h"
#include "Chat.h"
#include "DBCStores.h"
#include "Group.h"
#include "ObjectMgr.h"
#include "Objects/Bag.h"
#include "Objects/Item.h"
#include "Objects/ItemPrototype.h"
#include "Objects/Player.h"
#include "ScriptedGossip.h"
#include "Spells/SpellMgr.h"

#ifndef PlayerTalkClass
#define PlayerTalkClass (player->PlayerTalkClass)
#endif

struct ptr_master_npcAI : public ScriptedAI
{
    explicit ptr_master_npcAI(Creature* creature) : ScriptedAI(creature)
    {
        ptr_master_npcAI::Reset();
    }

    void Reset() override
    {
        if (sPTRConfig.IsEnabled())
            m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        else
            m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

        m_creature->AddUnitState(UNIT_STAT_ROOT);
    }

    void UpdateAI(uint32 const /*uiDiff*/) override
    {
        if (!sPTRConfig.IsEnabled() && m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
            m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        else if (sPTRConfig.IsEnabled() && !m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
            m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
    }
};

static Item* FindPlayerItemByEntry(Player* player, uint32 entry)
{
    if (!player)
        return nullptr;

    for (int i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; ++i)
        if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            if (pItem->GetEntry() == entry)
                return pItem;

    for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
        if (Bag* pBag = (Bag*)player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
                if (Item* pItem = pBag->GetItemByPos(j))
                    if (pItem->GetEntry() == entry)
                        return pItem;

    return nullptr;
}

static void MaximizeRidingSkills(Player* player)
{
    if (!player)
        return;

    // 1. Learn Journeyman Riding (33391) and Apprentice Riding (33388)
    if (!player->HasSpell(SPELL_JOURNEYMAN_RIDING))
        player->LearnSpell(SPELL_JOURNEYMAN_RIDING, false);
    if (!player->HasSpell(SPELL_APPRENTICE_RIDING))
        player->LearnSpell(SPELL_APPRENTICE_RIDING, false);

    // 2. Set unified Riding skill (SKILL_RIDING = 762) to maximum (150/150, step 2)
    player->SetSkill(SKILL_RIDING, SKILL_RIDING_MAX_VAL, SKILL_RIDING_MAX_VAL, 2);

    // 3. Learn all racial riding spells and skills for universal mount compatibility
    static const struct RacialRidingInfo
    {
        uint32 spellId;
        uint16 skillId;
    } racialRiding[] = {
        { 824,   SKILL_RIDING_HORSE },          // Horse Riding (Human)
        { 825,   SKILL_RIDING_WOLF },           // Wolf Riding (Orc)
        { 826,   SKILL_RIDING_RAM },            // Ram Riding (Dwarf)
        { 828,   SKILL_RIDING_TIGER },          // Tiger Riding (Night Elf)
        { 10861, SKILL_RIDING_RAPTOR },         // Raptor Riding (Troll)
        { 10906, SKILL_RIDING_UNDEAD_HORSE },   // Undead Horsemanship (Undead)
        { 10907, SKILL_RIDING_MECHANOSTRIDER }, // Mechanostrider Piloting (Gnome)
        { 18995, SKILL_RIDING_KODO }            // Kodo Riding (Tauren)
    };

    for (auto const& rr : racialRiding)
    {
        if (!player->HasSpell(rr.spellId))
            player->LearnSpell(rr.spellId, false);
        player->SetSkill(rr.skillId, SKILL_RIDING_MAX_VAL, SKILL_RIDING_MAX_VAL);
    }

    // 4. Teach Paladin / Warlock class mount spells
    if (player->GetClass() == CLASS_PALADIN)
    {
        if (!player->HasSpell(SPELL_PALADIN_WARHORSE))
            player->LearnSpell(SPELL_PALADIN_WARHORSE, false);
        if (!player->HasSpell(SPELL_PALADIN_CHARGER))
            player->LearnSpell(SPELL_PALADIN_CHARGER, false);
    }
    else if (player->GetClass() == CLASS_WARLOCK)
    {
        if (!player->HasSpell(SPELL_WARLOCK_FELSTEED))
            player->LearnSpell(SPELL_WARLOCK_FELSTEED, false);
        if (!player->HasSpell(SPELL_WARLOCK_DREADSTEED))
            player->LearnSpell(SPELL_WARLOCK_DREADSTEED, false);
    }
}

static void ApplyPTRBoostAndGear(Player* player, ClassesAndRoles const role)
{
    if (!player)
        return;

    // 1. Instant Level 60 Boost
    if (player->GetLevel() < 60)
    {
        player->SetLevel(60);
        player->InitTalentForLevel();
        player->SetUInt32Value(PLAYER_XP, 0);
    }

    // 2. Gold provisioning
    if (player->GetMoney() < sPTRConfig.GetGoldAmount())
        player->ModifyMoney(sPTRConfig.GetGoldAmount());

    // 3. 16-slot Bags (3 bags + 1 quiver for Hunters)
    if (sPTRConfig.GiveBags())
    {
        uint32 existingBags = player->GetItemCount(ITEM_BAG) + (player->GetClass() == CLASS_HUNTER ? 1 : 0);
        for (uint32 b = existingBags; b < 4; ++b)
        {
            player->StoreNewItemInBestSlots(ITEM_BAG, 1);
        }

        if (player->GetClass() == CLASS_HUNTER && !player->GetItemCount(ITEM_HUNTER_QUIVER))
        {
            player->StoreNewItemInBestSlots(ITEM_HUNTER_QUIVER, 1);
        }
    }

    // 4. Locate BiS items and weapon proficiencies for the requested role
    std::list<uint32_t> const* roleItems = nullptr;
    std::list<uint32_t> const* roleSpells = nullptr;

    for (auto const& entry : PTRGearData::GetBisItemsAndSpells())
    {
        if (std::get<0>(entry) == role)
        {
            roleItems = &std::get<1>(entry);
            roleSpells = &std::get<2>(entry);
            break;
        }
    }

    if (roleItems && roleSpells)
    {
        // Teach weapon proficiencies & abilities
        for (auto const& spellId : *roleSpells)
        {
            if (!player->HasSpell(spellId))
                player->LearnSpell(spellId, false);
        }

        // Unequip currently equipped items that do not belong to the selected role
        for (int slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
        {
            if (slot == EQUIPMENT_SLOT_BODY || slot == EQUIPMENT_SLOT_TABARD)
                continue;

            Item* equippedItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
            if (!equippedItem)
                continue;

            bool belongsToRole = false;
            for (auto const& roleItemId : *roleItems)
            {
                if (roleItemId == equippedItem->GetEntry())
                {
                    belongsToRole = true;
                    break;
                }
            }

            if (!belongsToRole)
            {
                player->AutoUnequipItemFromSlot(slot);
            }
        }

        // Distribute or equip BiS items with optimal PvE permanent enchantments
        for (auto const& itemId : *roleItems)
        {
            ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
            if (!proto)
                continue;

            player->SatisfyItemRequirements(proto);

            uint32 enchantId = 0;
            if (sPTRConfig.AutoEnchantBiS())
                enchantId = PTRGearData::GetOptimalEnchant(proto->InventoryType, role);

            Item* existingItem = FindPlayerItemByEntry(player, itemId);
            if (existingItem)
            {
                // If item is in the bag/inventory (not equipped)
                if (!existingItem->IsEquipped())
                {
                    uint16 dest = 0;
                    InventoryResult msg = player->CanEquipItem(NULL_SLOT, dest, existingItem, false);
                    if (msg != EQUIP_ERR_OK)
                        msg = player->CanEquipItem(NULL_SLOT, dest, existingItem, true);

                    if (msg == EQUIP_ERR_OK)
                    {
                        uint8 srcBag = existingItem->GetBagSlot();
                        uint8 srcSlot = existingItem->GetSlot();

                        Item* pDstItem = player->GetItemByPos(dest);
                        if (!pDstItem)
                        {
                            player->RemoveItem(srcBag, srcSlot, true);
                            player->EquipItem(dest, existingItem, true);
                            player->AutoUnequipOffhandIfNeed();
                        }
                        else
                        {
                            player->SwapItem(existingItem->GetPos(), dest);
                            player->AutoUnequipOffhandIfNeed();
                        }
                    }
                }

                // Ensure optimal PvE enchant is applied
                if (enchantId && existingItem->GetEnchantmentId(PERM_ENCHANTMENT_SLOT) != enchantId)
                {
                    if (existingItem->IsEquipped())
                        player->ApplyEnchantment(existingItem, PERM_ENCHANTMENT_SLOT, false);

                    existingItem->ClearEnchantment(PERM_ENCHANTMENT_SLOT);
                    existingItem->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantId, 0, 0);

                    if (existingItem->IsEquipped())
                        player->ApplyEnchantment(existingItem, PERM_ENCHANTMENT_SLOT, true);
                }
            }
            else
            {
                player->StoreNewItemInBestSlots(itemId, 1, enchantId);
            }
        }
    }

    // 6. Dynamic Class Spell Learning
    if (sPTRConfig.TeachClassSpells())
    {
        if (ChrClassesEntry const* clsEntry = sChrClassesStore.LookupEntry(player->GetClass()))
        {
            uint32 const family = clsEntry->spellfamily;

            for (uint32 i = 0; i < sObjectMgr.GetMaxSkillLineAbilityId(); ++i)
            {
                SkillLineAbilityEntry const* abilityEntry = sObjectMgr.GetSkillLineAbility(i);
                if (!abilityEntry)
                    continue;

                SpellEntry const* spellInfo = sSpellMgr.GetSpellEntry(abilityEntry->spellId);
                if (!spellInfo)
                    continue;

                // Skip server triggers
                if (spellInfo->spellLevel == 0)
                    continue;

                // Skip invalid class/race spells
                if (!player->IsSpellFitByClassAndRace(spellInfo->Id))
                    continue;

                // Skip unrelated spell families
                if (spellInfo->SpellFamilyName != family)
                    continue;

                // Skip talent abilities
                uint32 const firstRank = sSpellMgr.GetFirstSpellInChain(spellInfo->Id);
                if (GetTalentSpellCost(firstRank) > 0)
                    continue;

                // Validate spell
                if (!SpellMgr::IsSpellValid(spellInfo, player, false))
                    continue;

                player->LearnSpell(spellInfo->Id, false);
            }
        }
    }

    // 7. Max out skills to 300
    if (sPTRConfig.MaxSkills())
    {
        player->UpdateSkillsToMaxSkillsForLevel();
    }

    // 8. Max out Riding skills to maximum (Journeyman 150/150 and mount proficiencies)
    if (sPTRConfig.MaxRidingSkills())
    {
        MaximizeRidingSkills(player);
    }

    // 9. Optional: Provision race-appropriate epic mount item
    if (sPTRConfig.GiveMountItem())
    {
        uint32 mountEntry = 0;
        switch (player->GetRace())
        {
            case RACE_HUMAN:    mountEntry = 18776; break; // Armored Golden Steed
            case RACE_ORC:      mountEntry = 18796; break; // Armored Brown Wolf
            case RACE_DWARF:    mountEntry = 18785; break; // Armored White Ram
            case RACE_NIGHTELF: mountEntry = 18766; break; // Armored Frostsaber
            case RACE_UNDEAD:   mountEntry = 13334; break; // Armored Green Deathcharger
            case RACE_TAUREN:   mountEntry = 18793; break; // Armored White Kodo
            case RACE_GNOME:    mountEntry = 18772; break; // Armored Green Mechanostrider
            case RACE_TROLL:    mountEntry = 18788; break; // Armored Blue Raptor
            case RACE_HIGH_ELF: mountEntry = 80457; break; // Armored Thalassian Unicorn
            case RACE_GOBLIN:   mountEntry = 18796; break; // Armored Brown Wolf
            default:            mountEntry = 18776; break;
        }

        if (mountEntry && !FindPlayerItemByEntry(player, mountEntry))
        {
            player->StoreNewItemInBestSlots(mountEntry, 1);
        }
    }

    // 10. Restore health, powers and visual fanfare
    player->SetHealth(player->GetMaxHealth());
    for (int p = 0; p < MAX_POWERS; ++p)
    {
        player->SetPower(Powers(p), player->GetMaxPower(Powers(p)));
    }

    player->SendSpellGo(player, SPELL_BOOST_VISUAL);
    player->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);

    if (player->GetSession() && !player->GetSession()->IsHeadless())
    {
        ChatHandler(player).PSendSysMessage("|cff00ff00[PTR Master]|r Full Best-in-Slot raid package, spells, riding skills, and maximum skills equipped!");
    }
}

static void ApplyEquippedEnchants(Player* player)
{
    if (!player)
        return;

    ClassesAndRoles role = ClassesAndRoles::WARRIOR_FURY;
    switch (player->GetClass())
    {
        case CLASS_WARRIOR: role = ClassesAndRoles::WARRIOR_FURY; break;
        case CLASS_PALADIN: role = ClassesAndRoles::PALADIN_HOLY; break;
        case CLASS_HUNTER:  role = ClassesAndRoles::HUNTER; break;
        case CLASS_ROGUE:   role = ClassesAndRoles::ROGUE_SWORD; break;
        case CLASS_PRIEST:  role = ClassesAndRoles::PRIEST_HOLY; break;
        case CLASS_SHAMAN:  role = ClassesAndRoles::SHAMAN_RESTORATION; break;
        case CLASS_MAGE:    role = ClassesAndRoles::MAGE; break;
        case CLASS_WARLOCK: role = ClassesAndRoles::WARLOCK; break;
        case CLASS_DRUID:   role = ClassesAndRoles::DRUID_RESTORATION; break;
    }

    uint32 enchantCount = 0;
    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (!item || !item->GetProto())
            continue;

        uint32 enchantId = PTRGearData::GetOptimalEnchant(item->GetProto()->InventoryType, role);
        if (enchantId > 0)
        {
            item->ClearEnchantment(PERM_ENCHANTMENT_SLOT);
            item->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantId, 0, 0);
            player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, true);
            ++enchantCount;
        }
    }

    if (player->GetSession() && !player->GetSession()->IsHeadless())
    {
        ChatHandler(player).PSendSysMessage("|cff00ff00[PTR Master]|r Applied optimal PvE enchantments to %u equipped items.", enchantCount);
    }
}

ptr_master_npc::ptr_master_npc()
    : CreatureScript("ptr_master_npc")
{
}

CreatureAI* ptr_master_npc::GetAI(Creature* creature) const
{
    return new ptr_master_npcAI(creature);
}

bool ptr_master_npc::OnGossipHello(Player* player, Creature* creature)
{
    if (!player || !creature)
        return false;

    if (!sPTRConfig.IsEnabled())
        return false;

    if (sPTRConfig.IsGMOnly() && !player->IsGameMaster())
        return false;

    PlayerTalkClass->ClearMenus();

    // 1. Role-specific BiS packages
    switch (player->GetClass())
    {
        case CLASS_WARLOCK:
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Warlock (Plagueheart BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::WARLOCK));
            break;

        case CLASS_MAGE:
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Mage (Frostfire BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::MAGE));
            break;

        case CLASS_HUNTER:
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Hunter (Cryptstalker BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::HUNTER));
            break;

        case CLASS_PALADIN:
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Holy Paladin (Redemption BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::PALADIN_HOLY));
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Retribution Paladin (Avenger's BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::PALADIN_RETRIBUTION));
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Protection Paladin (Avenger's / Tank BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::PALADIN_PROTECTION));
            break;

        case CLASS_PRIEST:
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Holy Priest (Faith BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::PRIEST_HOLY));
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shadow Priest (Rime-Covered BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::PRIEST_SHADOW));
            break;

        case CLASS_ROGUE:
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Sword Rogue (Bonescythe / Gressil BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::ROGUE_SWORD));
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Dagger Rogue (Bonescythe / Kingsfall BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::ROGUE_DAGGER));
            break;

        case CLASS_SHAMAN:
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Restoration Shaman (Earthshatter BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::SHAMAN_RESTORATION));
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Elemental Shaman (Stormcaller BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::SHAMAN_ELEMENTAL));
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Enhancement Shaman (Stormcaller BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::SHAMAN_ENHANCEMENT));
            break;

        case CLASS_DRUID:
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Restoration Druid (Dreamwalker BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::DRUID_RESTORATION));
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Tank Druid (Feral Tank BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::DRUID_TANK));
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Balance Druid (Balance / Bloodvine BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::DRUID_BALANCE));
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Feral Druid (Feral Cat DPS BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::DRUID_FERAL));
            break;

        case CLASS_WARRIOR:
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Protection Warrior (Dreadnaught BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::WARRIOR_PROTECTION));
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Fury Warrior (Plated Abomination / Dual-Wield BiS Package)", GOSSIP_SENDER_MAIN, static_cast<uint32>(ClassesAndRoles::WARRIOR_FURY));
            break;
    }

    // 2. Extra Quality-of-Life Testing Options
    ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Grant all raid World Buffs", GOSSIP_SENDER_MAIN, ACTION_WORLDBUFF);
    ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Reset cooldowns & restore full powers", GOSSIP_SENDER_MAIN, ACTION_RESET_POWERS);
    ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Reset talents (Free respec)", GOSSIP_SENDER_MAIN, ACTION_RESET_TALENTS);
    ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Attune me to all raids & maximize reputations", GOSSIP_SENDER_MAIN, ACTION_ATTUNEMENTS);
    ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Enchant all my equipped gear", GOSSIP_SENDER_MAIN, ACTION_ENCHANT_GEAR);
    ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Teach maximum Riding skills (Journeyman 150)", GOSSIP_SENDER_MAIN, ACTION_MAX_RIDING);
    ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Teleport to Raid Boss Encounters...", GOSSIP_SENDER_MAIN, ACTION_TELEPORT_MENU);

    SEND_GOSSIP_MENU(TEXT_PTR_MASTER_GREETING, creature->GetGUID());
    return true;
}

bool ptr_master_npc::OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
{
    if (!player || !creature)
        return false;

    // Handle Teleportation Menu Sub-Page
    if (action == ACTION_TELEPORT_MENU)
    {
        PlayerTalkClass->ClearMenus();
        auto const& locations = PTRGearData::GetRaidLocations();
        for (size_t i = 0; i < locations.size(); ++i)
        {
            ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, locations[i].name.c_str(), GOSSIP_SENDER_MAIN, ACTION_TELEPORT_DEST_0 + static_cast<uint32>(i));
        }
        ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Back to Main Menu]", GOSSIP_SENDER_MAIN, ACTION_MAIN_MENU);
        SEND_GOSSIP_MENU(TEXT_PTR_MASTER_GREETING, creature->GetGUID());
        return true;
    }

    if (action == ACTION_MAIN_MENU)
    {
        return OnGossipHello(player, creature);
    }

    CLOSE_GOSSIP_MENU();

    // 1. Role BiS Gear Selections
    if (action >= static_cast<uint32>(ClassesAndRoles::WARLOCK) && action <= static_cast<uint32>(ClassesAndRoles::WARRIOR_FURY))
    {
        ApplyPTRBoostAndGear(player, static_cast<ClassesAndRoles>(action));
        return true;
    }

    // 2. World Buffs
    if (action == ACTION_WORLDBUFF)
    {
        for (auto const& buffId : PTRGearData::GetWorldBuffs())
        {
            creature->CastSpell(player, buffId, true);
        }
        if (player->GetSession() && !player->GetSession()->IsHeadless())
            ChatHandler(player).PSendSysMessage("|cff00ff00[PTR Master]|r Applied full world buff arsenal!");
        return true;
    }

    // 3. Reset Cooldowns & Restore Powers
    if (action == ACTION_RESET_POWERS)
    {
        player->RemoveAllSpellCooldown();
        player->SetHealth(player->GetMaxHealth());
        for (int p = 0; p < MAX_POWERS; ++p)
            player->SetPower(Powers(p), player->GetMaxPower(Powers(p)));

        if (player->GetSession() && !player->GetSession()->IsHeadless())
            ChatHandler(player).PSendSysMessage("|cff00ff00[PTR Master]|r Spell cooldowns wiped and full health/powers restored!");
        return true;
    }

    // 4. Free Talent Reset
    if (action == ACTION_RESET_TALENTS)
    {
        player->ResetTalents(true);
        if (player->GetSession() && !player->GetSession()->IsHeadless())
            ChatHandler(player).PSendSysMessage("|cff00ff00[PTR Master]|r Your talents have been cleanly reset!");
        return true;
    }

    // 5. Attunements & Reputations
    if (action == ACTION_ATTUNEMENTS)
    {
        if (sPTRConfig.GrantAttunements())
        {
            for (auto const& attuneSpell : PTRGearData::GetAttunementSpells())
            {
                if (!player->HasSpell(attuneSpell))
                    player->LearnSpell(attuneSpell, false);
            }
        }

        if (sPTRConfig.MaxRaidReputations())
        {
            static const uint32 raidFactions[] = { 529, 749, 910, 270 }; // Argent Dawn, Hydraxian, Brood of Nozdormu, Zandalar
            for (uint32 fId : raidFactions)
            {
                if (FactionEntry const* fEntry = sFactionStore.LookupEntry(fId))
                {
                    player->GetReputationMgr().SetReputation(fEntry, 42000);
                }
            }
        }

        if (player->GetSession() && !player->GetSession()->IsHeadless())
            ChatHandler(player).PSendSysMessage("|cff00ff00[PTR Master]|r Raid attunements and exalted reputations granted!");
        return true;
    }

    // 6. Enchant Equipped Gear
    if (action == ACTION_ENCHANT_GEAR)
    {
        ApplyEquippedEnchants(player);
        return true;
    }

    // 7. Max Riding Skill (Standalone Option)
    if (action == ACTION_MAX_RIDING)
    {
        MaximizeRidingSkills(player);
        if (player->GetSession() && !player->GetSession()->IsHeadless())
            ChatHandler(player).PSendSysMessage("|cff00ff00[PTR Master]|r Maximum Riding skill (Journeyman 150/150) and mount proficiencies learned!");
        return true;
    }

    // 8. Teleportation
    if (action >= ACTION_TELEPORT_DEST_0 && action <= ACTION_TELEPORT_DEST_7)
    {
        uint32 const destIndex = action - ACTION_TELEPORT_DEST_0;
        auto const& locations = PTRGearData::GetRaidLocations();
        if (destIndex < locations.size())
        {
            auto const& loc = locations[destIndex];

            if (sPTRConfig.RequireFullRaidGroup())
            {
                Group const* pGroup = player->GetGroup();
                if (!pGroup || !pGroup->isRaidGroup() || pGroup->GetMembersCount() < 10)
                {
                    if (player->GetSession() && !player->GetSession()->IsHeadless())
                        ChatHandler(player).PSendSysMessage("|cffff0000[PTR Master]|r Teleportation requires a full raid group with at least 10 members.");
                    return true;
                }
            }

            if (player->IsAlive())
            {
                player->TeleportTo(loc.mapId, loc.x, loc.y, loc.z, loc.o);
            }
        }
        return true;
    }

    return true;
}

void AddPTRMasterNPCScripts()
{
    new ptr_master_npc();
}
