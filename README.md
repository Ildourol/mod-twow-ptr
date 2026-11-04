# mod-twow-ptr: Turtle WoW Instant Testing Hub & Raid BiS Gearing NPC

A complete developer and PTR raid testing automation suite for the **Turtle WoW custom vMaNGOS** core (`tortoise-wow` targeting client 1.18.1.7272 / 1.12.1 network protocol).

![PTR Preview](preview.jpg)

---

## Features

* **Instant Level 60 Boost**: Instantly elevates character to level 60, resets XP, and prepares talent points.
* **19 Class/Spec Best-in-Slot (BiS) Packages**:
  - Full Tier 3 (Naxxramas) / Tier 2.5 (AQ40) armor sets.
  - Optimal weapons (Wraith Blade, Kingsfall, Corrupted Ashbringer, Gressil, The Hungering Cold, Might of Menethil, Nerubian Slavemaker).
  - Top-tier raid trinkets (Neltharion's Tear, Kiss of the Spider, Slayer's Crest, Rejuvenating Gem, Eye of the Dead, Drake Fang Talisman).
* **Automatic PvE BiS Permanent Enchanting**:
  - Automatically enchants all equipped items with optimal enchantments (+4 All Stats, Crusader, +30 Spell Damage, +55 Healing, Zandalar shoulder signets, Arcanum head/legs).
* **Skills & Dynamic Spell Discovery**:
  - Maxes out all weapon skills, defense, and class skills to 300/300.
  - Automatically queries the engine DBC and teaches all class spells and weapon proficiencies.
  - Automatically teaches and maxes out Riding skills to the maximum (Journeyman Riding 150/150 rank, Apprentice Riding 75, racial mount proficiencies, and Paladin/Warlock class mounts).
  - Standalone gossip option on PTR Master NPC to learn maximum riding skills at any time.
* **1,000 Gold & 16-Slot Bags**:
  - Spawns 1,000 gold and four 16-slot Traveler's Backpacks (3 + Harpy Hide Quiver for Hunters).
* **Instant Raid World Buff Dispenser**:
  - Grants Dragonslayer, Spirit of Zandalar, Warchief's Blessing, Dire Maul tributes, Songflower, and Sayge's Fortune.
* **Multi-Raid Boss Teleporter Hub**:
  - Instant teleportation to Scarlet Citadel (High Inquisitor Mariella), Naxxramas, Temple of Ahn'Qiraj (AQ40), Blackwing Lair, Molten Core, Tower of Karazhan, Emerald Sanctum, and Testing Grounds.
* **Consumables Vendor NPC (`Turtle`, Entry 2000101)**:
  - Sells 40+ flasks, combat elixirs, protection potions, free action potions, dark runes, oils, sharpening stones, totems, and food buffs.
* **Simulated Boss Dummy Loot Generator (`Loot Helper Dummy`, Entry 1001000)**:
  - Summons a simulated dummy for any raid boss (`.loothelper <entry>`).
  - Allows raids to test real boss loot table drops, rolling, master looter assignment, and client addon parsing without combat.
* **In-Game Commands**:
  - `.ptr spawn` - Summons the PTR Master NPC at current location.
  - `.ptr vendor` - Summons the Consumables Vendor at current location.
  - `.ptr clean` - Wipes all spell cooldowns and restores full health/powers.
  - `.loothelper [entry]` - Summons the boss loot helper dummy.

---

## Installation

From the TortoiseWoW source root, clone or copy the module directly into `modules/mod-twow-ptr/`.

```bash
git clone https://github.com/Ildourol/mod-twow-ptr.git modules/mod-twow-ptr
```

**Linux**

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DMODULE_MOD_TWOW_PTR=static
cmake --build build --parallel
```

**Windows** (PowerShell, Visual Studio 2022 with C++ tools)

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DMODULE_MOD_TWOW_PTR=static
cmake --build build --config Release --parallel
```

Preserve the CMake options for your existing server and modules. Deploy the rebuilt `mangosd` (`mangosd.exe` on Windows). Copy the module’s `conf/mod-twow-ptr.conf.dist` to `modules/mod-twow-ptr.conf` beside the active `mangosd.conf` and restart after completing any setup below.

**Database.** No manual import is needed when `Database.AutoUpdate.Enabled = 1`, `Database.AutoUpdate.AllowedModules` is `all` or includes `mod-twow-ptr`, and the server can read the module’s SQL at the source path used by the build. With the standard database folder names, the core applies `data/sql/world/` at startup. Keep `Database.AutoUpdate.SortByName = 1` and check the startup log. For a manual install, back up the affected databases, apply the files in filename order to the matching databases, and exclude this module from the updater.

Install on a test realm.

## Configuration (`mod-twow-ptr.conf`)

| Setting | Default | Description |
|:---|:---:|:---|
| `PTR.Enable` | `1` | Master toggle enabling or disabling the PTR Master module. |
| `PTR.GMOnly` | `0` | If `1`, only accounts with GM privileges (`gmlevel >= 1`) can use PTR gossip. |
| `PTR.GoldAmount` | `10000000` | Copper amount given on boost (10000000 copper = 1000 gold). |
| `PTR.GiveBags` | `1` | Automatically equips four 16-slot bags (or 3 bags + quiver for hunters). |
| `PTR.MaxSkills` | `1` | Updates weapon skills, defense, and class skills to 300. |
| `PTR.MaxRidingSkills` | `1` | Automatically teaches and maxes out Riding skills (Journeyman Riding 150/150 and mount proficiencies). |
| `PTR.GiveMountItem` | `1` | Automatically stores a race-appropriate epic mount item in player bags upon gearing. |
| `PTR.TeachClassSpells` | `1` | Automatically learns all class spells up to max rank. |
| `PTR.AutoEnchantBiS` | `1` | Automatically enchants equipped BiS items with optimal PvE enchantments. |
| `PTR.GrantAttunements` | `1` | Grants key raid attunements (MC, BWL, Onyxia, Naxxramas). |
| `PTR.MaxRaidReputations` | `1` | Sets raid reputations (Argent Dawn, Hydraxian, Nozdormu, Zandalar) to Exalted. |
| `PTR.RaidTeleport.RequireFullGroup` | `0` | If `1`, requires a full raid group of 10+ players to teleport to raid encounters. |
| `PTR.LootHelper.Enabled` | `1` | Enables the Boss Dummy Loot Generator and `.loothelper` command. |
| `PTR.LootHelper.GMOnly` | `1` | Restricts the `.loothelper` command to GMs. |

---

## In-Game Commands

* `.ptr` - Shows command usage.
* `.ptr spawn` - Summons `Keklord Faelan Tordring` (Entry 2000100).
* `.ptr vendor` - Summons `Turtle` Consumables Vendor (Entry 2000101).
* `.ptr clean` - Resets cooldowns and powers.
* `.loothelper [creature_entry]` - Summons `Loot Helper Dummy` (Entry 1001000) mimicking the specified boss.

---

## World Spawns (Capital Cities & Banks)

Both NPCs (`Keklord` & `Turtle`) are permanently spawned inside or outside the bank in all major capital cities and hubs (`data/sql/world/004_ptr_spawns.sql`):
* **Alliance**: Stormwind City (Trade District), Ironforge (The Commons), Darnassus (Bank Terrace), Alah'Thalas (High Elf Plaza).
* **Horde**: Orgrimmar (Valley of Strength), Undercity (Central Ring), Thunder Bluff (Lower Rise Totem), Sparkwater Port (Goblin Bank).
* **Neutral / Goblin Hubs**: Booty Bay, Gadgetzan, Ratchet, Everlook.
* **Testing Grounds**: Scarlet Citadel Staging Hub (Map 451).


---

## Immutability Compliance

This module adheres strictly to **The Unediting Doctrine**. It modifies zero core files in `tortoise-wow` and zero files in `TortoiseBots`. All hooks are implemented via `CreatureScript`, `WorldScript`, and `AllCommandScript`.
