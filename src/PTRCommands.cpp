#include "PTRCommands.h"
#include "PTRCommon.h"
#include "PTRConfig.h"
#include "PTRLootHelper.h"
#include "Chat.h"
#include "Maps/Map.h"
#include "Objects/Player.h"
#include "ObjectMgr.h"

#include <cstring>
#include <string>

PTRCommandScript::PTRCommandScript()
    : AllCommandScript("PTRCommandScript")
{
}

bool PTRCommandScript::CanExecuteCommand(ChatHandler* handler, char const* cmd, char const* argsIn)
{
    if (!cmd || !handler)
        return true;

    Player* player = handler->GetSession() ? handler->GetSession()->GetPlayer() : nullptr;
    if (!player)
        return true;

    if (strcmp(cmd, "ptr") == 0)
    {
        std::string rest = argsIn ? argsIn : "";
        auto const takeWord = [&rest]() -> std::string
        {
            size_t const b = rest.find_first_not_of(' ');
            if (b == std::string::npos) { rest.clear(); return std::string(); }
            size_t const e = rest.find(' ', b);
            std::string word = rest.substr(b, e == std::string::npos ? std::string::npos : e - b);
            rest = e == std::string::npos ? std::string() : rest.substr(e + 1);
            return word;
        };

        std::string const sub = takeWord();

        if (sub == "spawn")
        {
            if (sPTRConfig.IsGMOnly() && !player->IsGameMaster())
            {
                handler->SendSysMessage("You do not have permission to spawn PTR NPCs.");
                return false;
            }

            Creature* master = player->SummonCreature(
                NPC_PTR_MASTER,
                player->GetPositionX(),
                player->GetPositionY(),
                player->GetPositionZ(),
                player->GetOrientation(),
                TEMPSUMMON_MANUAL_DESPAWN,
                0
            );

            if (master)
                handler->SendSysMessage("|cff00ff00[PTR Master]|r Spawned PTR Master NPC successfully.");
            else
                handler->SendSysMessage("|cffff0000[PTR Master]|r Failed to spawn PTR Master NPC.");

            return false;
        }
        else if (sub == "vendor")
        {
            if (sPTRConfig.IsGMOnly() && !player->IsGameMaster())
            {
                handler->SendSysMessage("You do not have permission to spawn PTR NPCs.");
                return false;
            }

            Creature* vendor = player->SummonCreature(
                NPC_PTR_VENDOR,
                player->GetPositionX(),
                player->GetPositionY(),
                player->GetPositionZ(),
                player->GetOrientation(),
                TEMPSUMMON_MANUAL_DESPAWN,
                0
            );

            if (vendor)
                handler->SendSysMessage("|cff00ff00[PTR Master]|r Spawned PTR Consumables Vendor successfully.");
            else
                handler->SendSysMessage("|cffff0000[PTR Master]|r Failed to spawn PTR Consumables Vendor.");

            return false;
        }
        else if (sub == "clean")
        {
            player->RemoveAllSpellCooldown();
            player->SetHealth(player->GetMaxHealth());
            for (int p = 0; p < MAX_POWERS; ++p)
                player->SetPower(Powers(p), player->GetMaxPower(Powers(p)));

            handler->SendSysMessage("|cff00ff00[PTR Master]|r Cooldowns cleared and powers restored.");
            return false;
        }
        else
        {
            handler->SendSysMessage("|cff00ff00Turtle WoW PTR Master Commands:|r");
            handler->SendSysMessage("  .ptr spawn       - Spawn PTR Master Gearing NPC at your location");
            handler->SendSysMessage("  .ptr vendor      - Spawn PTR Consumables Vendor NPC at your location");
            handler->SendSysMessage("  .ptr clean       - Reset all cooldowns and restore full health/powers");
            handler->SendSysMessage("  .loothelper [id] - Spawn simulated boss dummy loot generator");
            return false;
        }
    }
    else if (strcmp(cmd, "loothelper") == 0)
    {
        if (!sPTRConfig.IsLootHelperEnabled())
        {
            handler->SendSysMessage("The Loot Helper system is disabled by server configuration.");
            return false;
        }

        if (sPTRConfig.IsLootHelperGMOnly() && !player->IsGameMaster())
        {
            handler->SendSysMessage("You do not have permission to use the loot helper command.");
            return false;
        }

        uint32 entry = 0;
        Creature* target = nullptr;
        if (handler->GetSession() && handler->GetSession()->GetPlayer())
        {
            Player* p = handler->GetSession()->GetPlayer();
            target = p->GetMap()->GetAnyTypeCreature(p->GetSelectionGuid());
        }

        if (target)
        {
            entry = target->GetEntry();
        }
        else if (argsIn && argsIn[0] != '\0')
        {
            entry = static_cast<uint32>(strtoul(argsIn, nullptr, 10));
        }

        if (entry == 0)
        {
            handler->SendSysMessage("Error: No boss creature targeted and no valid entry provided.");
            handler->SendSysMessage("Usage: Target a boss or type '.loothelper <creature_entry>'");
            return false;
        }

        CreatureInfo const* creatureTemplate = sObjectMgr.GetCreatureTemplate(entry);
        if (!creatureTemplate)
        {
            handler->PSendSysMessage("Error: Creature template %u does not exist.", entry);
            return false;
        }

        Creature* lootHelper = player->SummonCreature(
            NPC_PTR_LOOT_HELPER,
            player->GetPositionX(),
            player->GetPositionY(),
            player->GetPositionZ(),
            player->GetOrientation(),
            TEMPSUMMON_CORPSE_TIMED_DESPAWN,
            1000 * 60 * 5
        );

        if (!lootHelper)
        {
            handler->SendSysMessage("System Error: Failed to summon Loot Helper Dummy.");
            return false;
        }

        ptr_loot_helperAI* lootAI = dynamic_cast<ptr_loot_helperAI*>(lootHelper->AI());
        if (!lootAI)
        {
            handler->SendSysMessage("System Error: Loot Helper Dummy has invalid AI.");
            return false;
        }

        lootAI->SetCreatureEntry(entry);
        handler->PSendSysMessage("|cff00ff00[Loot Helper]|r Spawned dummy for boss '%s' (Entry %u). Speak to it to simulate loot drops.",
            creatureTemplate->name.c_str(), entry);

        return false;
    }

    return true;
}

void AddPTRCommandScripts()
{
    new PTRCommandScript();
}
