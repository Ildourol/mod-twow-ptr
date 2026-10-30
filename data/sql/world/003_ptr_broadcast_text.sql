-- ============================================================================
-- mod-twow-ptr: Broadcast Text and NPC Dialog Text
-- Entries:
--   1000100: PTR Master Greeting
--   1001000: Loot Helper Dummy Greeting
-- ============================================================================

-- PTR Master Dialog
DELETE FROM `npc_text` WHERE `ID` = 1000100;
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`) VALUES
(1000100, 1000100, 1.0);

DELETE FROM `broadcast_text` WHERE `entry` = 1000100;
INSERT INTO `broadcast_text` (`entry`, `male_text`, `female_text`, `chat_type`, `sound_id`, `language_id`, `emote_id1`, `emote_id2`, `emote_id3`, `emote_delay1`, `emote_delay2`, `emote_delay3`) VALUES
(1000100, 'Welcome to the Turtle WoW PTR Testing Suite!$B\nSelect your class specialization to instantly receive full Best-in-Slot raid gear, 1,000 gold, 16-slot bags, trained abilities, and maximum weapon skills. You can also acquire full raid world buffs or teleport directly to raid encounters!', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- Loot Helper Dummy Dialog
DELETE FROM `npc_text` WHERE `ID` = 1001000;
INSERT INTO `npc_text` (`ID`, `BroadcastTextID0`, `Probability0`) VALUES
(1001000, 1001000, 1.0);

DELETE FROM `broadcast_text` WHERE `entry` = 1001000;
INSERT INTO `broadcast_text` (`entry`, `male_text`, `female_text`, `chat_type`, `sound_id`, `language_id`, `emote_id1`, `emote_id2`, `emote_id3`, `emote_delay1`, `emote_delay2`, `emote_delay3`) VALUES
(1001000, 'Loot Helper Dummy active.$B\nThis dummy can simulate a completed boss encounter, triggering the boss loot table and gold drop for your raid party to verify master loot distribution and addon parsing.', NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
