-- ============================================================================
-- mod-twow-ptr: World Spawns Migration
-- Places Keklord the Gearing Master (2000100) and Turtle the Vendor (2000101)
-- in all major capital cities inside or outside the bank, plus testing hub:
--
-- ALLIANCE CAPITALS:
--   1. Stormwind City (Trade District Bank)
--   2. Ironforge (The Commons Bank)
--   3. Darnassus (Bank Terrace / Temple Gardens)
--   4. Alah'Thalas (Turtle WoW High Elf Capital Plaza / Bank)
--
-- HORDE CAPITALS:
--   5. Orgrimmar (Valley of Strength Bank)
--   6. Undercity (Central Bank Ring)
--   7. Thunder Bluff (Lower Rise Bank Totem)
--   8. Sparkwater Port (Turtle WoW Goblin Capital Bank)
--
-- NEUTRAL / GOBLIN HUBS:
--   9. Booty Bay (Outside Bank)
--   10. Gadgetzan (Outside Bank)
--   11. Ratchet (Outside Bank)
--   12. Everlook (Outside Bank)
--
-- TESTING GROUND:
--   13. Scarlet Citadel Staging Hub (Map 451)
-- ============================================================================

DELETE FROM `creature` WHERE `guid` BETWEEN 3000101 AND 3000130;

-- ----------------------------------------------------------------------------
-- 1. Testing Hub: Scarlet Citadel Staging Hub (Map 451)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000101, 2000100, 0, 0, 0, 451, 4579.22, -300.771, 270.233, 1.6003, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000102, 2000101, 0, 0, 0, 451, 4577.31, -301.759, 270.235, 1.5375, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 2. Stormwind City: Trade District Bank (Map 0)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000103, 2000100, 0, 0, 0, 0, -8925.50, 614.20, 99.61, 3.65, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000104, 2000101, 0, 0, 0, 0, -8927.80, 617.50, 99.61, 3.65, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 3. Ironforge: The Commons Bank (Map 0)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000105, 2000100, 0, 0, 0, 0, -4881.50, -991.20, 504.02, 5.40, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000106, 2000101, 0, 0, 0, 0, -4884.10, -993.80, 504.02, 5.40, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 4. Darnassus: Bank Terrace / Temple Gardens (Map 1)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000107, 2000100, 0, 0, 0, 1, 9940.50, 2510.80, 1317.66, 1.25, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000108, 2000101, 0, 0, 0, 1, 9943.20, 2512.50, 1317.66, 1.25, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 5. Alah'Thalas: High Elf Capital Plaza / Bank (Map 0)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000109, 2000100, 0, 0, 0, 0, 3212.50, -2501.20, 111.75, 3.50, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000110, 2000101, 0, 0, 0, 0, 3215.10, -2503.40, 111.75, 3.50, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 6. Orgrimmar: Valley of Strength Bank (Map 1)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000111, 2000100, 0, 0, 0, 1, 1624.80, -4373.50, 11.81, 0.45, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000112, 2000101, 0, 0, 0, 1, 1627.50, -4370.20, 11.81, 0.45, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 7. Undercity: Central Bank Ring (Map 0)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000113, 2000100, 0, 0, 0, 0, 1600.80, 246.50, -52.06, 4.70, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000114, 2000101, 0, 0, 0, 0, 1603.20, 244.10, -52.06, 4.70, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 8. Thunder Bluff: Lower Rise Bank Totem (Map 1)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000115, 2000100, 0, 0, 0, 1, -1254.50, 28.20, 128.27, 4.85, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000116, 2000101, 0, 0, 0, 1, -1257.20, 29.80, 128.27, 4.85, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 9. Sparkwater Port: Goblin Capital Bank (Map 1)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000117, 2000100, 0, 0, 0, 1, 842.50, -5053.80, 6.03, 1.95, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000118, 2000101, 0, 0, 0, 1, 845.20, -5051.50, 6.03, 1.95, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 10. Booty Bay: Outside Bank (Map 0)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000119, 2000100, 0, 0, 0, 0, -14415.80, 523.50, 5.24, 2.10, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000120, 2000101, 0, 0, 0, 0, -14418.20, 521.80, 5.24, 2.10, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 11. Gadgetzan: Outside Bank (Map 1)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000121, 2000100, 0, 0, 0, 1, -7198.50, -3830.20, 8.64, 3.14, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000122, 2000101, 0, 0, 0, 1, -7200.80, -3832.90, 8.64, 3.14, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 12. Ratchet: Outside Bank (Map 1)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000123, 2000100, 0, 0, 0, 1, -910.20, -3724.80, 9.71, 0.35, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000124, 2000101, 0, 0, 0, 1, -912.50, -3722.10, 9.71, 0.35, 25, 25, 0, 100, 100, 0, 1, 200);

-- ----------------------------------------------------------------------------
-- 13. Everlook: Outside Bank (Map 1)
-- ----------------------------------------------------------------------------
INSERT INTO `creature`
  (`guid`, `id`, `id2`, `id3`, `id4`, `map`, `position_x`, `position_y`, `position_z`, `orientation`,
   `spawntimesecsmin`, `spawntimesecsmax`, `wander_distance`, `health_percent`, `mana_percent`, `movement_type`, `spawn_flags`, `visibility_mod`)
VALUES
  (3000125, 2000100, 0, 0, 0, 1, 6780.20, -4675.50, 723.97, 5.80, 25, 25, 0, 100, 100, 0, 1, 200),
  (3000126, 2000101, 0, 0, 0, 1, 6782.80, -4673.20, 723.97, 5.80, 25, 25, 0, 100, 100, 0, 1, 200);
