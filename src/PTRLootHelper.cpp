#include "PTRLootHelper.h"
#include "PTRCommon.h"
#include "PTRConfig.h"
#include "ObjectMgr.h"
#include "Objects/Player.h"
#include "Objects/TemporarySummon.h"
#include "Chat.h"
#include "ScriptedGossip.h"

#include <sstream>

#ifndef PlayerTalkClass
#define PlayerTalkClass (player->PlayerTalkClass)
#endif

ptr_loot_helperAI::ptr_loot_helperAI(Creature* creature)
    : ScriptedAI(creature)
{
    ptr_loot_helperAI::Reset();
}

void ptr_loot_helperAI::Reset()
{
    SetPlayerVisibility(false);
}

void ptr_loot_helperAI::SetPlayerVisibility(bool visible)
{
    m_visibleToPlayers = visible;
    if (m_creature)
    {
        m_creature->SetVisibility(visible ? VISIBILITY_ON : VISIBILITY_OFF);
    }
}

static void KillCreature(Player* player, Creature* creature)
{
    if (player && creature)
    {
        player->DealDamage(creature, creature->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
    }
}

static void EraseCreature(Player* player, Creature* creature)
{
    if (!creature)
        return;

    if (TemporarySummon* summon = dynamic_cast<TemporarySummon*>(creature))
    {
        summon->UnSummon();
    }
    else if (player)
    {
        KillCreature(player, creature);
    }
}

ptr_loot_helper::ptr_loot_helper()
    : CreatureScript("ptr_loot_helper")
{
}

CreatureAI* ptr_loot_helper::GetAI(Creature* creature) const
{
    return new ptr_loot_helperAI(creature);
}

bool ptr_loot_helper::OnGossipHello(Player* player, Creature* creature)
{
    if (!player || !creature)
        return false;

    if (!sPTRConfig.IsLootHelperEnabled())
        return false;

    ptr_loot_helperAI* ai = dynamic_cast<ptr_loot_helperAI*>(creature->AI());
    if (!ai)
        return false;

    if (!ai->IsVisibleToPlayers() && !player->IsGameMaster())
    {
        CLOSE_GOSSIP_MENU();
        return false;
    }

    PlayerTalkClass->ClearMenus();

    if (ai->GetCreatureEntry() == 0)
    {
        ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "This helper must be spawned via '.loothelper <entry>' while targeting a boss.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        if (player->IsGameMaster())
            ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Erase me.", GOSSIP_SENDER_MAIN, GOSSIP_ERASE_ME);
        SEND_GOSSIP_MENU(TEXT_PTR_LOOT_HELPER, creature->GetGUID());
        return true;
    }

    CreatureInfo const* creatureTemplate = sObjectMgr.GetCreatureTemplate(ai->GetCreatureEntry());
    if (!creatureTemplate)
    {
        ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Invalid boss creature entry.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        if (player->IsGameMaster())
            ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Erase me.", GOSSIP_SENDER_MAIN, GOSSIP_ERASE_ME);
        SEND_GOSSIP_MENU(TEXT_PTR_LOOT_HELPER, creature->GetGUID());
        return true;
    }

    if (player->IsGameMaster())
    {
        std::stringstream ss;
        ss << "Target Boss: " << creatureTemplate->name << " (Entry " << ai->GetCreatureEntry() << ")\n";
        ss << "Visibility: " << (ai->IsVisibleToPlayers() ? "Visible to raid" : "Hidden (GM Only)");
        ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ss.str().c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
    }

    ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Generate boss loot and make dummy lootable.", GOSSIP_SENDER_MAIN, GOSSIP_GENERATE_LOOT_CONFIRM);

    if (player->IsGameMaster())
    {
        if (ai->IsVisibleToPlayers())
            ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Hide dummy from players.", GOSSIP_SENDER_MAIN, GOSSIP_HIDE_FROM_PLAYERS);
        else
            ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Show dummy to players.", GOSSIP_SENDER_MAIN, GOSSIP_SHOW_TO_PLAYERS);

        ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Erase dummy.", GOSSIP_SENDER_MAIN, GOSSIP_ERASE_ME);
    }

    SEND_GOSSIP_MENU(TEXT_PTR_LOOT_HELPER, creature->GetGUID());
    return true;
}

bool ptr_loot_helper::OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
{
    if (!player || !creature)
        return false;

    ptr_loot_helperAI* ai = dynamic_cast<ptr_loot_helperAI*>(creature->AI());
    if (!ai)
        return false;

    if (!ai->IsVisibleToPlayers() && !player->IsGameMaster())
    {
        CLOSE_GOSSIP_MENU();
        return false;
    }

    if (action == GOSSIP_HIDE_FROM_PLAYERS && player->IsGameMaster())
    {
        ai->SetPlayerVisibility(false);
        CLOSE_GOSSIP_MENU();
        return true;
    }
    else if (action == GOSSIP_SHOW_TO_PLAYERS && player->IsGameMaster())
    {
        ai->SetPlayerVisibility(true);
        CLOSE_GOSSIP_MENU();
        return true;
    }
    else if (action == GOSSIP_ERASE_ME && player->IsGameMaster())
    {
        CLOSE_GOSSIP_MENU();
        EraseCreature(player, creature);
        return true;
    }
    else if (action == GOSSIP_GENERATE_LOOT_CONFIRM)
    {
        PlayerTalkClass->ClearMenus();
        ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "WARNING: This will simulate a boss kill and generate drop loot for your raid group.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "CONFIRM: Generate simulated boss loot now.", GOSSIP_SENDER_MAIN, GOSSIP_GENERATE_LOOT_EXEC);
        SEND_GOSSIP_MENU(TEXT_PTR_LOOT_HELPER, creature->GetGUID());
        return true;
    }
    else if (action == GOSSIP_GENERATE_LOOT_EXEC)
    {
        CLOSE_GOSSIP_MENU();

        CreatureInfo const* creatureTemplate = sObjectMgr.GetCreatureTemplate(ai->GetCreatureEntry());
        if (!creatureTemplate)
            return false;

        creature->SetLootRecipient(player);
        creature->SetLootIdOverride(creatureTemplate->loot_id);
        creature->SetGoldOverride(creatureTemplate->gold_min, creatureTemplate->gold_max);

        KillCreature(player, creature);
        return true;
    }

    CLOSE_GOSSIP_MENU();
    return true;
}

void AddPTRLootHelperScripts()
{
    new ptr_loot_helper();
}
