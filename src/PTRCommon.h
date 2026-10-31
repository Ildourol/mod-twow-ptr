#ifndef _PTR_COMMON_H_
#define _PTR_COMMON_H_

#include <cstdint>
#include <string>
#include <vector>
#include <list>
#include <tuple>

enum class ClassesAndRoles : uint32_t
{
    WARLOCK = 20,
    MAGE,
    HUNTER,
    PALADIN_HOLY,
    PALADIN_RETRIBUTION,
    PALADIN_PROTECTION,
    PRIEST_HOLY,
    PRIEST_SHADOW,
    ROGUE_SWORD,
    ROGUE_DAGGER,
    SHAMAN_RESTORATION,
    SHAMAN_ELEMENTAL,
    SHAMAN_ENHANCEMENT,
    DRUID_RESTORATION,
    DRUID_TANK,
    DRUID_BALANCE,
    DRUID_FERAL,
    WARRIOR_PROTECTION,
    WARRIOR_FURY
};

struct RaidLocation
{
    std::string name;
    uint32_t mapId;
    float x;
    float y;
    float z;
    float o;
};

// Target creature entries
static constexpr uint32_t NPC_PTR_MASTER      = 2000100;
static constexpr uint32_t NPC_PTR_VENDOR      = 2000101;
static constexpr uint32_t NPC_PTR_LOOT_HELPER = 1001000;

// Default items & visual spells
static constexpr uint32_t ITEM_BAG            = 4500;  // Traveler's Backpack (16 slot)
static constexpr uint32_t ITEM_HUNTER_QUIVER  = 19319; // Harpy Hide Quiver (16 slot, 15% haste)
static constexpr uint32_t SPELL_BOOST_VISUAL  = 24240; // Visual boost effect

// Riding Skills and Spells
static constexpr uint32_t SKILL_RIDING_ID             = 762;
static constexpr uint16_t SKILL_RIDING_MAX_VAL        = 150;
static constexpr uint32_t SPELL_APPRENTICE_RIDING     = 33388;
static constexpr uint32_t SPELL_JOURNEYMAN_RIDING     = 33391;

// Class Mount Spells
static constexpr uint32_t SPELL_PALADIN_WARHORSE      = 13819;
static constexpr uint32_t SPELL_PALADIN_CHARGER       = 23214;
static constexpr uint32_t SPELL_WARLOCK_FELSTEED      = 5784;
static constexpr uint32_t SPELL_WARLOCK_DREADSTEED    = 23161;

// Gossip Text entries
static constexpr uint32_t TEXT_PTR_MASTER_GREETING = 1000100;
static constexpr uint32_t TEXT_PTR_LOOT_HELPER     = 1001000;

// Gossip action offsets
enum PTRGossipActions : uint32_t
{
    ACTION_WORLDBUFF        = 5001,
    ACTION_RESET_POWERS     = 5002,
    ACTION_RESET_TALENTS    = 5003,
    ACTION_ATTUNEMENTS      = 5004,
    ACTION_ENCHANT_GEAR     = 5005,
    ACTION_TELEPORT_MENU    = 5006,
    ACTION_MAX_RIDING       = 5007,
    ACTION_TELEPORT_DEST_0  = 5100, // Mariella / Scarlet Citadel
    ACTION_TELEPORT_DEST_1  = 5101, // Naxxramas Entrance
    ACTION_TELEPORT_DEST_2  = 5102, // Temple of Ahn'Qiraj (AQ40)
    ACTION_TELEPORT_DEST_3  = 5103, // Blackwing Lair
    ACTION_TELEPORT_DEST_4  = 5104, // Molten Core
    ACTION_TELEPORT_DEST_5  = 5105, // Tower of Karazhan
    ACTION_TELEPORT_DEST_6  = 5106, // Emerald Sanctum
    ACTION_TELEPORT_DEST_7  = 5107, // Testing Yard (Target Dummies)
    ACTION_MAIN_MENU        = 5199
};

// Loot helper actions
enum LootHelperGossipActions : uint32_t
{
    GOSSIP_HIDE_FROM_PLAYERS   = 6001,
    GOSSIP_SHOW_TO_PLAYERS     = 6002,
    GOSSIP_ERASE_ME            = 6003,
    GOSSIP_GENERATE_LOOT_CONFIRM = 6004,
    GOSSIP_GENERATE_LOOT_EXEC  = 6005
};

#endif
