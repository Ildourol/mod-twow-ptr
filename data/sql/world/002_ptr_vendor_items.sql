-- ============================================================================
-- mod-twow-ptr: Consumables Vendor Inventory
-- Populates npc_vendor for PTR Consumables Vendor (Entry 2000101)
-- ============================================================================

DELETE FROM `npc_vendor` WHERE `entry` = 2000101;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `itemflags`, `condition_id`) VALUES
(2000101, 1, 13510, 0, 0, 0, 0),  -- Flask of the Titans
(2000101, 2, 13511, 0, 0, 0, 0),  -- Flask of Distilled Wisdom
(2000101, 3, 13512, 0, 0, 0, 0),  -- Flask of Supreme Power
(2000101, 4, 13513, 0, 0, 0, 0),  -- Flask of Chromatic Resistance
(2000101, 5, 20081, 0, 0, 0, 0),  -- Swiftness of Zanza
(2000101, 6, 20079, 0, 0, 0, 0),  -- Spirit of Zanza
(2000101, 7, 20080, 0, 0, 0, 0),  -- Sheen of Zanza
(2000101, 8, 13452, 0, 0, 0, 0),  -- Elixir of the Mongoose
(2000101, 9, 20007, 0, 0, 0, 0),  -- Mageblood Potion
(2000101, 10, 3825, 0, 0, 0, 0),  -- Elixir of Fortitude
(2000101, 11, 13445, 0, 0, 0, 0), -- Elixir of Superior Defense
(2000101, 12, 20004, 0, 0, 0, 0), -- Major Troll's Blood Potion
(2000101, 13, 9088, 0, 0, 0, 0),  -- Gift of Arthas
(2000101, 14, 12451, 0, 0, 0, 0), -- Juju Power
(2000101, 15, 9206, 0, 0, 0, 0),  -- Elixir of Giants
(2000101, 16, 12460, 0, 0, 0, 0), -- Juju Might
(2000101, 17, 12820, 0, 0, 0, 0), -- Winterfall Firewater
(2000101, 18, 13454, 0, 0, 0, 0), -- Greater Arcane Elixir
(2000101, 19, 9264, 0, 0, 0, 0),  -- Elixir of Shadow Power
(2000101, 20, 21546, 0, 0, 0, 0), -- Elixir of Greater Firepower
(2000101, 21, 17708, 0, 0, 0, 0), -- Elixir of Frost Power
(2000101, 22, 13461, 0, 0, 0, 0), -- Greater Arcane Protection Potion
(2000101, 23, 13457, 0, 0, 0, 0), -- Greater Fire Protection Potion
(2000101, 24, 13456, 0, 0, 0, 0), -- Greater Frost Protection Potion
(2000101, 25, 13458, 0, 0, 0, 0), -- Greater Nature Protection Potion
(2000101, 26, 13459, 0, 0, 0, 0), -- Greater Shadow Protection Potion
(2000101, 27, 13928, 0, 0, 0, 0), -- Grilled Squid
(2000101, 28, 20452, 0, 0, 0, 0), -- Smoked Desert Dumplings
(2000101, 29, 13931, 0, 0, 0, 0), -- Nightfin Soup
(2000101, 30, 21151, 0, 0, 0, 0), -- Rumsey Rum Black Label
(2000101, 31, 20748, 0, 0, 0, 0), -- Brilliant Mana Oil
(2000101, 32, 20749, 0, 0, 0, 0), -- Brilliant Wizard Oil
(2000101, 33, 18262, 0, 0, 0, 0), -- Elemental Sharpening Stone
(2000101, 34, 13444, 0, 0, 0, 0), -- Major Mana Potion
(2000101, 35, 13446, 0, 0, 0, 0), -- Major Healing Potion
(2000101, 36, 3387, 0, 0, 0, 0),  -- Limited Invulnerability Potion
(2000101, 37, 9030, 0, 0, 0, 0),  -- Restorative Potion
(2000101, 38, 5634, 0, 0, 0, 0),  -- Free Action Potion
(2000101, 39, 20520, 0, 0, 0, 0), -- Dark Rune
(2000101, 40, 12662, 0, 0, 0, 0), -- Demonic Rune
(2000101, 41, 5175, 0, 0, 0, 0),  -- Earth Totem
(2000101, 42, 5176, 0, 0, 0, 0),  -- Fire Totem
(2000101, 43, 5177, 0, 0, 0, 0),  -- Water Totem
(2000101, 44, 5178, 0, 0, 0, 0);  -- Air Totem
