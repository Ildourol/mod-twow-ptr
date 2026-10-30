#include "PTRGearData.h"
#include "ItemPrototype.h"

namespace PTRGearData
{
    // =========================================================================
    // 1. Warlock
    // =========================================================================
    static const std::list<uint32_t> m_lWarlockBIS =
    {
        22506, // Plagueheart Circlet
        21608, // Amulet of Vek'nilash
        22507, // Plagueheart Shoulderpads
        23050, // Cloak of the Necropolis
        22504, // Plagueheart Robe
        21186, // Rockfury Bracers
        22807, // Wraith Blade
        23049, // Sapphiron's Left Eye
        22820, // Wand of Fates
        21585, // Dark Storm Gauntlets
        22730, // Eyestalk Waist Cord
        23070, // Leggings of Polarity
        22508, // Plagueheart Sandals
        23031, // Band of the Inevitable
        19379, // Neltharion's Tear
        21709, // Ring of the Fallen God
        23046  // The Restrained Essence of Sapphiron
    };

    static const std::list<uint32_t> m_lWarlockSpells =
    {
        201,  // One-Handed Swords
        227,  // Staves
        1180  // Daggers
    };

    // =========================================================================
    // 2. Mage
    // =========================================================================
    static const std::list<uint32_t> m_lMageBIS =
    {
        22498, // Frostfire Circlet
        23057, // Gem of Trapped Innocents
        22983, // Rime Covered Mantle
        23050, // Cloak of the Necropolis
        22496, // Frostfire Robe
        23021, // The Soul Harvester's Bindings
        22807, // Wraith Blade
        23049, // Sapphiron's Left Eye
        22821, // Doomfinger
        21585, // Dark Storm Gauntlets
        22730, // Eyestalk Waist Cord
        23070, // Leggings of Polarity
        22500, // Frostfire Sandals
        23237, // Ring of the Eternal Flame
        23062, // Frostfire Ring
        23046, // The Restrained Essence of Sapphiron
        19379  // Neltharion's Tear
    };

    static const std::list<uint32_t> m_lMageSpells =
    {
        201,  // One-Handed Swords
        227,  // Staves
        1180  // Daggers
    };

    // =========================================================================
    // 3. Hunter
    // =========================================================================
    static const std::list<uint32_t> m_lHunterBIS =
    {
        22438, // Cryptstalker Headpiece
        23053, // Stormrage's Talisman of Seething
        22439, // Cryptstalker Spaulders
        23045, // Shroud of Dominion
        22436, // Cryptstalker Tunic
        22443, // Cryptstalker Wristguards
        22816, // Hatchet of Sundered Bone
        22802, // Kingsfall
        22812, // Nerubian Slavemaker
        16571, // General's Chain Gloves
        22442, // Cryptstalker Girdle
        22437, // Cryptstalker Legguards
        22440, // Cryptstalker Boots
        23067, // Ring of the Cryptstalker
        22961, // Band of Reanimation
        21670, // Badge of the Swarmguard
        23041, // Slayer's Crest
        19319  // Harpy Hide Quiver
    };

    static const std::list<uint32_t> m_lHunterSpells =
    {
        674,   // Dual Wield
        264,   // Bows
        201,   // One-Handed Swords
        197,   // Two-Handed Axes
        227,   // Staves
        200,   // Polearms
        202,   // Two-Handed Swords
        196,   // One-Handed Axes
        266,   // Guns
        1180,  // Daggers
        15590, // Fist Weapons
        5011,  // Crossbows
        3127   // Parry
    };

    // =========================================================================
    // 4. Paladin
    // =========================================================================
    static const std::list<uint32_t> m_lHolyPaladinBIS =
    {
        19375, // Mish'undare, Circlet of the Mind Flayer
        23057, // Gem of Trapped Innocents
        22429, // Redemption Spaulders
        23050, // Cloak of the Necropolis
        22425, // Redemption Tunic
        21604, // Bracelets of Royal Redemption
        23056, // Hammer of the Twisting Nether
        23075, // Death's Bargain
        23006, // Libram of Light
        20264, // Peacekeeper Gauntlets
        21582, // Grasp of the Old God
        22427, // Redemption Legguards
        22430, // Redemption Boots
        19382, // Pure Elementium Band
        23066, // Ring of Redemption
        23047, // Eye of the Dead
        19395  // Rejuvenating Gem
    };

    static const std::list<uint32_t> m_lRetributionPaladinBIS =
    {
        21387, // Avenger's Crown
        18404, // Onyxia Tooth Pendant
        21391, // Avenger's Pauldrons
        23045, // Shroud of Dominion
        21389, // Avenger's Breastplate
        22936, // Wristguards of Vengeance
        22691, // Corrupted Ashbringer
        23203, // Libram of Fervor
        21623, // Gauntlets of the Righteous Champion
        23219, // Girdle of the Mentor
        21390, // Avenger's Legguards
        21388, // Avenger's Greaves
        23038, // Band of Unnatural Forces
        21205, // Signet Ring of the Bronze Dragonflight
        22321, // Heart of Wyrmthalak
        19289  // Darkmoon Card: Maelstrom
    };

    static const std::list<uint32_t> m_lProtectionPaladinBIS =
    {
        21387, // Avenger's Crown
        22732, // Mark of C'Thun
        21639, // Pauldrons of the Unrelenting
        22938, // Cryptfiend Silk Cloak
        21389, // Avenger's Breastplate
        18754, // Fel Hardened Bracers
        23577, // The Hungering Cold
        22818, // The Plague Bearer
        22401, // Libram of Hope
        21674, // Gauntlets of Steadfast Determination
        21598, // Royal Qiraji Belt
        19855, // Bloodsoaked Legplates
        21706, // Boots of the Unwavering Will
        21200, // Signet Ring of the Bronze Dragonflight
        21601, // Ring of Emperor Vek'lor
        19431, // Styleen's Impeding Scarab
        18406  // Onyxia Blood Talisman
    };

    static const std::list<uint32_t> m_lPaladinSpells =
    {
        199,  // Two-Handed Maces
        201,  // One-Handed Swords
        197,  // Two-Handed Axes
        200,  // Polearms
        202,  // Two-Handed Swords
        196,  // One-Handed Axes
        198,  // One-Handed Maces
        3127, // Parry
        107,  // Block
        750   // Plate Mail
    };

    // =========================================================================
    // 5. Priest
    // =========================================================================
    static const std::list<uint32_t> m_lHolyPriestBIS =
    {
        22514, // Circlet of Faith
        21712, // Amulet of the Fallen God
        22515, // Shoulderpads of Faith
        22960, // Cloak of Suturing
        22512, // Robe of Faith
        21604, // Bracelets of Royal Redemption
        23056, // Hammer of the Twisting Nether
        23048, // Sapphiron's Right Eye
        23009, // Wand of the Whispering Dead
        22517, // Gloves of Faith
        21582, // Grasp of the Old God
        22513, // Leggings of Faith
        22516, // Sandals of Faith
        23061, // Ring of Faith
        22939, // Band of Unanswered Prayers
        23027, // Warmth of Forgiveness
        23047  // Eye of the Dead
    };

    static const std::list<uint32_t> m_lShadowPriestBIS =
    {
        23035, // Preceptor's Hat
        18814, // Choker of the Fire Lord
        22983, // Rime Covered Mantle
        22731, // Cloak of the Devoured
        23220, // Crystal Webbed Robe
        21611, // Burrower Bracers
        22988, // The End of Dreams
        23049, // Sapphiron's Left Eye
        21603, // Wand of Qiraji Nobility
        21585, // Dark Storm Gauntlets
        19400, // Firemaw's Clutch
        19133, // Fel Infused Leggings
        19131, // Snowblind Shoes
        21709, // Ring of the Fallen God
        21210, // Signet Ring of the Bronze Dragonflight
        19379, // Neltharion's Tear
        23046  // The Restrained Essence of Sapphiron
    };

    static const std::list<uint32_t> m_lPriestSpells =
    {
        227,  // Staves
        198,  // One-Handed Maces
        1180  // Daggers
    };

    // =========================================================================
    // 6. Rogue
    // =========================================================================
    static const std::list<uint32_t> m_lSwordRogueBIS =
    {
        22478, // Bonescythe Helmet
        19377, // Prestor's Talisman of Connivery
        22479, // Bonescythe Pauldrons
        23045, // Shroud of Dominion
        22476, // Bonescythe Breastplate
        22483, // Bonescythe Bracers
        23054, // Gressil, Dawn of Ruin
        23577, // The Hungering Cold
        22812, // Nerubian Slavemaker
        22481, // Bonescythe Gauntlets
        21586, // Belt of Never-ending Agony
        22477, // Bonescythe Legplates
        22480, // Bonescythe Sabatons
        23060, // Bonescythe Ring
        23038, // Band of Unnatural Forces
        23041, // Slayer's Crest
        22954  // Kiss of the Spider
    };

    static const std::list<uint32_t> m_lDaggerRogueBIS =
    {
        22478, // Bonescythe Helmet
        19377, // Prestor's Talisman of Connivery
        22479, // Bonescythe Pauldrons
        23045, // Shroud of Dominion
        22476, // Bonescythe Breastplate
        22483, // Bonescythe Bracers
        22802, // Kingsfall
        21126, // Death's Sting
        22812, // Nerubian Slavemaker
        22481, // Bonescythe Gauntlets
        21586, // Belt of Never-ending Agony
        22477, // Bonescythe Legplates
        22480, // Bonescythe Sabatons
        23060, // Bonescythe Ring
        23038, // Band of Unnatural Forces
        23041, // Slayer's Crest
        22954  // Kiss of the Spider
    };

    static const std::list<uint32_t> m_lRogueSpells =
    {
        674,   // Dual Wield
        264,   // Bows
        201,   // One-Handed Swords
        198,   // One-Handed Maces
        266,   // Guns
        1180,  // Daggers
        15590, // Fist Weapons
        5011,  // Crossbows
        3127   // Parry
    };

    // =========================================================================
    // 7. Shaman
    // =========================================================================
    static const std::list<uint32_t> m_lRestorationShamanBIS =
    {
        22466, // Earthshatter Headpiece
        21712, // Amulet of the Fallen God
        22467, // Earthshatter Spaulders
        21583, // Cloak of Clarity
        22464, // Earthshatter Tunic
        22471, // Earthshatter Wristguards
        23056, // Hammer of the Twisting Nether
        22819, // Shield of Condemnation
        22396, // Totem of Life
        21619, // Gloves of the Messiah
        22470, // Earthshatter Girdle
        22465, // Earthshatter Legguards
        22468, // Earthshatter Boots
        21620, // Ring of the Martyr
        23065, // Ring of the Earthshatterer
        17064, // Shard of the Scale
        19395  // Rejuvenating Gem
    };

    static const std::list<uint32_t> m_lElementalShamanBIS =
    {
        19375, // Mish'undare, Circlet of the Mind Flayer
        22943, // Malice Stone Pendant
        21376, // Stormcaller's Pauldrons
        23050, // Cloak of the Necropolis
        21671, // Robes of the Battleguard
        21464, // Shackles of the Unscarred
        22988, // The End of Dreams
        23049, // Sapphiron's Left Eye
        23199, // Totem of the Storm
        21585, // Dark Storm Gauntlets
        22730, // Eyestalk Waist Cord
        21375, // Stormcaller's Leggings
        21373, // Stormcaller's Footguards
        21707, // Ring of Swarming Thought
        21709, // Ring of the Fallen God
        19379, // Neltharion's Tear
        23046  // The Restrained Essence of Sapphiron
    };

    static const std::list<uint32_t> m_lEnhancementShamanBIS =
    {
        18817, // Crown of Destruction
        18404, // Onyxia Tooth Pendant
        21684, // Mantle of the Desert's Fury
        23045, // Shroud of Dominion
        21374, // Stormcaller's Hauberk
        21602, // Qiraji Execution Bracers
        22798, // Might of Menethil
        22395, // Totem of Rage
        21624, // Gauntlets of Kalimdor
        21586, // Belt of Never-ending Agony
        21651, // Scaled Sand Reaver Leggings
        21705, // Boots of the Fallen Prophet
        17063, // Band of Accuria
        23038, // Band of Unnatural Forces
        22321, // Heart of Wyrmthalak
        19289  // Darkmoon Card: Maelstrom
    };

    static const std::list<uint32_t> m_lShamanSpells =
    {
        199,   // Two-Handed Maces
        197,   // Two-Handed Axes
        227,   // Staves
        196,   // One-Handed Axes
        198,   // One-Handed Maces
        1180,  // Daggers
        15590, // Fist Weapons
        107    // Block
    };

    // =========================================================================
    // 8. Druid
    // =========================================================================
    static const std::list<uint32_t> m_lRestorationDruidBIS =
    {
        21615, // Don Rigoberto's Lost Hat
        21712, // Amulet of the Fallen God
        22491, // Dreamwalker Spaulders
        22960, // Cloak of Suturing
        22488, // Dreamwalker Tunic
        21604, // Bracelets of Royal Redemption
        23056, // Hammer of the Twisting Nether
        23048, // Sapphiron's Right Eye
        22399, // Idol of Health
        22493, // Dreamwalker Handguards
        21582, // Grasp of the Old God
        22489, // Dreamwalker Legguards
        22492, // Dreamwalker Boots
        21620, // Ring of the Martyr
        22939, // Band of Unanswered Prayers
        23047, // Eye of the Dead
        23027  // Warmth of Forgiveness
    };

    static const std::list<uint32_t> m_lTankDruidBIS =
    {
        21693, // Guise of the Devourer
        22732, // Mark of C'Thun
        20194, // Defiler's Leather Shoulders
        22938, // Cryptfiend Silk Cloak
        23226, // Ghoul Skin Tunic
        22663, // Polar Bracers
        943,   // Warden Staff
        23198, // Idol of Brutality
        21605, // Gloves of the Hidden Temple
        21675, // Thick Qirajihide Belt
        22740, // Outrider's Leather Pants
        19381, // Boots of the Shadow Flame
        21601, // Ring of Emperor Vek'lor
        23018, // Signet of the Fallen Defender
        13966, // Mark of Tyranny
        11811  // Smoking Heart of the Mountain
    };

    static const std::list<uint32_t> m_lBalanceDruidBIS =
    {
        19375, // Mish'undare, Circlet of the Mind Flayer
        23057, // Gem of Trapped Innocents
        22983, // Rime Covered Mantle
        23050, // Cloak of the Necropolis
        19682, // Bloodvine Vest
        23021, // The Soul Harvester's Bindings
        22988, // The End of Dreams
        23049, // Sapphiron's Left Eye
        23197, // Idol of the Moon
        21585, // Dark Storm Gauntlets
        22730, // Eyestalk Waist Cord
        19683, // Bloodvine Leggings
        19684, // Bloodvine Boots
        23025, // Seal of the Damned
        21709, // Ring of the Fallen God
        19379, // Neltharion's Tear
        23046  // The Restrained Essence of Sapphiron
    };

    static const std::list<uint32_t> m_lFeralDruidBIS =
    {
        8345,  // Wolfshead Helm
        19377, // Prestor's Talisman of Connivery
        21665, // Mantle of Wicked Revenge
        21710, // Cloak of the Fallen God
        23226, // Ghoul Skin Tunic
        21602, // Qiraji Execution Bracers
        22988, // The End of Dreams
        13385, // Tome of Knowledge
        23198, // Idol of Brutality
        21672, // Gloves of Enforcement
        21586, // Belt of Never-ending Agony
        23071, // Leggings of Apocalypse
        21493, // Boots of the Vanguard
        23038, // Band of Unnatural Forces
        19432, // Circle of Applied Force
        19406, // Drake Fang Talisman
        23041  // Slayer's Crest
    };

    static const std::list<uint32_t> m_lDruidSpells =
    {
        199,   // Two-Handed Maces
        227,   // Staves
        198,   // One-Handed Maces
        1180,  // Daggers
        15590  // Fist Weapons
    };

    // =========================================================================
    // 9. Warrior
    // =========================================================================
    static const std::list<uint32_t> m_lProtectionWarriorBIS =
    {
        22418, // Dreadnaught Helmet
        22732, // Mark of C'Thun
        22419, // Dreadnaught Pauldrons
        22938, // Cryptfiend Silk Cloak
        22416, // Dreadnaught Breastplate
        22423, // Dreadnaught Bracers
        23577, // The Hungering Cold
        23043, // The Face of Death
        19368, // Dragonbreath Hand Cannon
        22421, // Dreadnaught Gauntlets
        22422, // Dreadnaught Waistguard
        22417, // Dreadnaught Legplates
        22420, // Dreadnaught Sabatons
        23059, // Ring of the Dreadnaught
        21601, // Ring of Emperor Vek'lor
        19431, // Styleen's Impeding Scarab
        19406  // Drake Fang Talisman
    };

    static const std::list<uint32_t> m_lFuryWarriorBIS =
    {
        12640, // Lionheart Helm
        18404, // Onyxia Tooth Pendant
        21330, // Conqueror's Spaulders
        23045, // Shroud of Dominion
        23000, // Plated Abomination Ribcage
        22936, // Wristguards of Vengeance
        23054, // Gressil, Dawn of Ruin
        23577, // The Hungering Cold
        17069, // Striker's Mark
        21581, // Gauntlets of Annihilation
        19137, // Onslaught Girdle
        22385, // Titanic Leggings
        19381, // Boots of the Shadow Flame
        23038, // Band of Unnatural Forces
        19384, // Master Dragonslayer's Ring
        19406, // Drake Fang Talisman
        21670  // Badge of the Swarmguard
    };

    static const std::list<uint32_t> m_lWarriorSpells =
    {
        674,   // Dual Wield
        199,   // Two-Handed Maces
        264,   // Bows
        201,   // One-Handed Swords
        197,   // Two-Handed Axes
        227,   // Staves
        200,   // Polearms
        202,   // Two-Handed Swords
        196,   // One-Handed Axes
        198,   // One-Handed Maces
        266,   // Guns
        1180,  // Daggers
        15590, // Fist Weapons
        5011,  // Crossbows
        3127,  // Parry
        107,   // Block
        750,   // Plate Mail
        2458,  // Berserker Stance
        71     // Defensive Stance
    };

    // =========================================================================
    // Master Mapping
    // =========================================================================
    static const std::vector<std::tuple<ClassesAndRoles, std::list<uint32_t>, std::list<uint32_t>>> m_vBisItemsAndSpells =
    {
        std::make_tuple(ClassesAndRoles::WARLOCK, m_lWarlockBIS, m_lWarlockSpells),
        std::make_tuple(ClassesAndRoles::MAGE, m_lMageBIS, m_lMageSpells),
        std::make_tuple(ClassesAndRoles::HUNTER, m_lHunterBIS, m_lHunterSpells),
        std::make_tuple(ClassesAndRoles::PALADIN_HOLY, m_lHolyPaladinBIS, m_lPaladinSpells),
        std::make_tuple(ClassesAndRoles::PALADIN_RETRIBUTION, m_lRetributionPaladinBIS, m_lPaladinSpells),
        std::make_tuple(ClassesAndRoles::PALADIN_PROTECTION, m_lProtectionPaladinBIS, m_lPaladinSpells),
        std::make_tuple(ClassesAndRoles::PRIEST_HOLY, m_lHolyPriestBIS, m_lPriestSpells),
        std::make_tuple(ClassesAndRoles::PRIEST_SHADOW, m_lShadowPriestBIS, m_lPriestSpells),
        std::make_tuple(ClassesAndRoles::ROGUE_SWORD, m_lSwordRogueBIS, m_lRogueSpells),
        std::make_tuple(ClassesAndRoles::ROGUE_DAGGER, m_lDaggerRogueBIS, m_lRogueSpells),
        std::make_tuple(ClassesAndRoles::SHAMAN_RESTORATION, m_lRestorationShamanBIS, m_lShamanSpells),
        std::make_tuple(ClassesAndRoles::SHAMAN_ELEMENTAL, m_lElementalShamanBIS, m_lShamanSpells),
        std::make_tuple(ClassesAndRoles::SHAMAN_ENHANCEMENT, m_lEnhancementShamanBIS, m_lShamanSpells),
        std::make_tuple(ClassesAndRoles::DRUID_RESTORATION, m_lRestorationDruidBIS, m_lDruidSpells),
        std::make_tuple(ClassesAndRoles::DRUID_TANK, m_lTankDruidBIS, m_lDruidSpells),
        std::make_tuple(ClassesAndRoles::DRUID_BALANCE, m_lBalanceDruidBIS, m_lDruidSpells),
        std::make_tuple(ClassesAndRoles::DRUID_FERAL, m_lFeralDruidBIS, m_lDruidSpells),
        std::make_tuple(ClassesAndRoles::WARRIOR_PROTECTION, m_lProtectionWarriorBIS, m_lWarriorSpells),
        std::make_tuple(ClassesAndRoles::WARRIOR_FURY, m_lFuryWarriorBIS, m_lWarriorSpells)
    };

    std::vector<std::tuple<ClassesAndRoles, std::list<uint32_t>, std::list<uint32_t>>> const& GetBisItemsAndSpells()
    {
        return m_vBisItemsAndSpells;
    }

    // =========================================================================
    // World Buffs
    // =========================================================================
    static const std::list<uint32_t> m_lWorldBuffs =
    {
        22888, // Rallying Cry of the Dragonslayer
        24425, // Spirit of Zandalar
        16609, // Warchief's Blessing
        22818, // Mol'dar's Moxie (Dire Maul)
        22820, // Slip'kik's Savvy (Dire Maul)
        22817, // Fengus' Ferocity (Dire Maul)
        15366, // Songflower Serenade
        23737  // Sayge's Dark Fortune of Stamina
    };

    std::list<uint32_t> const& GetWorldBuffs()
    {
        return m_lWorldBuffs;
    }

    // =========================================================================
    // Attunements
    // =========================================================================
    static const std::list<uint32_t> m_lAttunementSpells =
    {
        21677, // Attunement to the Core (Molten Core)
        23420  // Blackhand's Command (Blackwing Lair)
    };

    std::list<uint32_t> const& GetAttunementSpells()
    {
        return m_lAttunementSpells;
    }

    // =========================================================================
    // Raid Teleport Locations
    // =========================================================================
    static const std::vector<RaidLocation> m_vRaidLocations =
    {
        // 0: High Inquisitor Mariella (Scarlet Citadel)
        { "High Inquisitor Mariella (Scarlet Citadel)", 451, 232.119843f, 25.800516f, 30.823233f, 3.145022f },
        // 1: Naxxramas (Sapphiron Staging)
        { "Naxxramas (Sapphiron / Kel'Thuzad)", 533, 3005.87f, -3435.01f, 293.88f, 0.0f },
        // 2: Temple of Ahn'Qiraj (C'Thun / Twin Emperors)
        { "Temple of Ahn'Qiraj (AQ40)", 531, -8212.0f, 2049.0f, 129.0f, 0.0f },
        // 3: Blackwing Lair (Nefarian)
        { "Blackwing Lair (BWL)", 469, -7673.0f, -1109.0f, 396.0f, 0.6f },
        // 4: Molten Core (Ragnaros)
        { "Molten Core (MC)", 409, 1092.0f, -467.0f, -104.0f, 3.6f },
        // 5: Tower of Karazhan (Turtle WoW Custom Raid)
        { "Tower of Karazhan", 0, -11118.0f, -2004.0f, 49.0f, 0.7f },
        // 6: Emerald Sanctum (Turtle WoW Custom Raid)
        { "Emerald Sanctum", 1, -2824.0f, -2487.0f, 89.0f, 0.0f },
        // 7: Testing Yard (Target Dummies)
        { "Testing Grounds (Target Dummies)", 0, -4981.0f, -929.0f, 501.0f, 5.4f }
    };

    std::vector<RaidLocation> const& GetRaidLocations()
    {
        return m_vRaidLocations;
    }

    // =========================================================================
    // Optimal PvE BiS Permanent Enchantments (DBC SpellItemEnchantmentEntry IDs)
    // =========================================================================
    uint32_t GetOptimalEnchant(uint32_t inventoryType, ClassesAndRoles role)
    {
        const bool isHealer = (role == ClassesAndRoles::PALADIN_HOLY ||
                               role == ClassesAndRoles::PRIEST_HOLY ||
                               role == ClassesAndRoles::SHAMAN_RESTORATION ||
                               role == ClassesAndRoles::DRUID_RESTORATION);

        const bool isCaster = (role == ClassesAndRoles::WARLOCK ||
                               role == ClassesAndRoles::MAGE ||
                               role == ClassesAndRoles::PRIEST_SHADOW ||
                               role == ClassesAndRoles::SHAMAN_ELEMENTAL ||
                               role == ClassesAndRoles::DRUID_BALANCE);

        const bool isTank = (role == ClassesAndRoles::WARRIOR_PROTECTION ||
                             role == ClassesAndRoles::PALADIN_PROTECTION ||
                             role == ClassesAndRoles::DRUID_TANK);

        switch (inventoryType)
        {
            case INVTYPE_HEAD:
            case INVTYPE_LEGS:
                if (isHealer) return 2585; // Presence of Sight / Healing Focus
                if (isCaster) return 2583; // Arcanum of Focus (+8 Spell Damage)
                if (isTank)   return 2590; // Syncretist's Sigil (+10 Defense, +100 HP)
                return 2588;               // Falcon's Call (+24 AP, +1% Hit)

            case INVTYPE_SHOULDERS:
                if (isHealer) return 2545; // Zandalar Signet of Serenity (+33 Healing)
                if (isCaster) return 2543; // Zandalar Signet of Mojo (+18 Spell Damage)
                return 2544;               // Zandalar Signet of Might (+30 Attack Power)

            case INVTYPE_CLOAK:
                if (isTank) return 1889;   // Greater Resistance (+5 All Resist)
                return 1890;               // Subtlety (-2% Threat)

            case INVTYPE_CHEST:
            case INVTYPE_ROBE:
                return 1891;               // Greater Stats (+4 All Stats)

            case INVTYPE_WRISTS:
                if (isHealer) return 2565; // Healing Power (+24 Healing)
                if (isCaster) return 2566; // Mana Regeneration (+4 MP5)
                if (isTank)   return 1885; // Superior Stamina (+9 Stamina)
                return 1886;               // Superior Strength (+9 Strength)

            case INVTYPE_HANDS:
                if (isTank) return 2621;   // Threat (+1% Threat / +10 Defense)
                return 2564;               // Greater Agility (+7 Agility)

            case INVTYPE_FEET:
                if (isTank) return 1893;   // Greater Stamina (+7 Stamina)
                return 911;                // Minor Speed (Run speed increase)

            case INVTYPE_WEAPON:
            case INVTYPE_WEAPONMAINHAND:
            case INVTYPE_WEAPONOFFHAND:
                if (isHealer) return 2505; // Healing Power (+55 Healing)
                if (isCaster) return 2504; // Spell Power (+30 Spell Damage)
                if (isTank)   return 1897; // Crusader
                return 1897;               // Crusader

            case INVTYPE_2HWEAPON:
                if (isHealer) return 2505; // Healing Power (+55 Healing)
                if (isCaster) return 2504; // Spell Power (+30 Spell Damage)
                return 1897;               // Crusader

            case INVTYPE_SHIELD:
                return 2605;               // Greater Stamina (+7 Stamina)

            default:
                return 0;
        }
    }
}
