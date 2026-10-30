-- ============================================================================
-- mod-twow-ptr: Creature Templates Migration
-- Adds PTR Master Gearing NPC (2000100), Consumables Vendor (2000101),
-- and Boss Dummy Loot Generator (1001000).
-- ============================================================================

-- 1. PTR Master Gearing NPC: Keklord Faelan Tordring
DELETE FROM `creature_template` WHERE `entry` = 2000100;
INSERT INTO `creature_template`
  (`entry`, `name`, `subname`, `display_id1`, `faction`, `npc_flags`, `gossip_menu_id`,
   `level_min`, `level_max`, `health_min`, `health_max`, `mana_min`, `mana_max`, `armor`,
   `unit_class`, `type`, `speed_walk`, `speed_run`, `scale`, `base_attack_time`, `ranged_attack_time`,
   `dmg_min`, `dmg_max`, `movement_type`, `inhabit_type`, `regeneration`, `ai_name`, `script_name`)
VALUES
  (2000100, 'Keklord Faelan Tordring', 'PTR Testing Master', 10341, 35, 1, 0,
   60, 60, 700000, 700000, 5000000, 5000000, 4500,
   1, 7, 1.0, 1.14, 1.0, 1000, 3700,
   5000, 7000, 0, 3, 1, '', 'ptr_master_npc');

-- 2. PTR Consumables Vendor: Turtle
DELETE FROM `creature_template` WHERE `entry` = 2000101;
INSERT INTO `creature_template`
  (`entry`, `name`, `subname`, `display_id1`, `faction`, `npc_flags`, `gossip_menu_id`,
   `level_min`, `level_max`, `health_min`, `health_max`, `mana_min`, `mana_max`, `armor`,
   `unit_class`, `type`, `speed_walk`, `speed_run`, `scale`, `base_attack_time`, `ranged_attack_time`,
   `dmg_min`, `dmg_max`, `movement_type`, `inhabit_type`, `regeneration`, `ai_name`, `script_name`)
VALUES
  (2000101, 'Turtle', 'PTR Consumables Vendor', 16259, 35, 128, 0,
   60, 60, 700000, 700000, 5000000, 5000000, 4500,
   1, 7, 1.0, 1.14, 0.25, 1000, 3700,
   5000, 7000, 0, 3, 1, '', 'ptr_vendor_npc');

-- 3. Boss Dummy Loot Generator
DELETE FROM `creature_template` WHERE `entry` = 1001000;
INSERT INTO `creature_template`
  (`entry`, `name`, `subname`, `display_id1`, `faction`, `npc_flags`, `gossip_menu_id`,
   `level_min`, `level_max`, `health_min`, `health_max`, `mana_min`, `mana_max`, `armor`,
   `unit_class`, `type`, `speed_walk`, `speed_run`, `scale`, `base_attack_time`, `ranged_attack_time`,
   `dmg_min`, `dmg_max`, `movement_type`, `inhabit_type`, `regeneration`, `ai_name`, `script_name`)
VALUES
  (1001000, 'Loot Helper Dummy', 'Simulated Boss Drop', 10341, 35, 1, 0,
   60, 60, 1000, 1000, 0, 0, 100,
   1, 7, 1.0, 1.14, 0.75, 2000, 2000,
   1, 2, 0, 3, 1, '', 'ptr_loot_helper');
