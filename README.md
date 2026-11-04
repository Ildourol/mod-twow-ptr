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

These steps assume you have a working [TortoiseWoW](https://github.com/Penqle/tortoise-wow) source checkout, initialized core databases, and the server data files for your realm. Use a core revision compatible with this module. Run all build and SQL commands from the core source root, the directory containing the core's `CMakeLists.txt`.


### 1. Add the module and build on Linux

Use Git, CMake, a C++17 compiler, and the core's build dependencies. On Debian or Ubuntu, a typical starting point is:

```bash
sudo apt update
sudo apt install git cmake build-essential libace-dev default-libmysqlclient-dev libssl-dev zlib1g-dev
```

Use your distribution's `mysql` or `mariadb` command-line client if importing SQL manually. Keep any additional dependency and CMake settings required by your core and other enabled modules.

```bash
cd /path/to/tortoise-wow
git clone https://github.com/Ildourol/mod-twow-ptr.git modules/mod-twow-ptr
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$PWD/server-stage" -DMODULE_MOD_TWOW_PTR=static
cmake --build build --parallel
cmake --install build
```

### 2. Add the module and build on Windows

Install Git for Windows, CMake 3.21 or later, and Visual Studio 2022 or its Build Tools with **Desktop development with C++** and a Windows SDK. Open PowerShell with Git and CMake on `PATH`. Use an x64 build and the dependency setup of your working core.

```powershell
Set-Location 'C:\src\tortoise-wow'
git clone https://github.com/Ildourol/mod-twow-ptr.git modules/mod-twow-ptr
cmake -S . -B build-vs -G "Visual Studio 17 2022" -A x64 "-DCMAKE_INSTALL_PREFIX=$PWD/server-stage" -DMODULE_MOD_TWOW_PTR=static
cmake --build build-vs --config Release --parallel
cmake --install build-vs --config Release
```

Check each command for errors before continuing. Both builds include `mangosd`. If the configure output reports an unused module switch, verify the source placement before building. The two build sections are platform alternatives. If you already have a module checkout, use it in place of the clone. A full directory copy, a Linux symlink, or a Windows directory junction works as long as `modules/mod-twow-ptr/src/` is directly below the module directory. The module directory name determines the CMake switch and loader symbol. If reusing a build directory, keep its generator and architecture and preserve the switches for your other modules. Reconfigure after adding the module and verify CMake lists it as static.

The staged world server is normally `server-stage/bin/mangosd` on Linux and `server-stage/mangosd.exe` on Windows. Stop the running world server before deploying the rebuilt executable and any required runtime libraries or module assets. Preserve the live configuration and data files. The paths below assume the standard staged layout. For an existing deployment, use the directory containing the active `mangosd.conf`, including a custom path passed via `-c`.

### 3. Set up the database

Back up the affected databases. The examples use `tw_char` and `tw_world` as database names. Substitute the names from the active `CharacterDatabase.Info` and `WorldDatabase.Info` settings as applicable, plus your database user and any connection options.

Choose 1 import method. For the core auto-updater, verify that `Database.AutoUpdate.Enabled` and `Database.AutoUpdate.SortByName` are enabled, that `Database.AutoUpdate.AllowedModules` includes `mod-twow-ptr` (or uses `all`), and that the runtime host can access the module checkout at the source path embedded by the build. The updater uses the configured `CharUpdateName` and `WorldUpdateName` under `data/sql/` (normally `character` and `world`). Check the first startup log for applied updates. If importing manually, exclude this module from the updater allowlist to avoid replaying the same files. Preserve other modules that use automatic updates.

**Manual import on Linux (Bash)**

```bash
mysql -u root -p tw_world < "modules/mod-twow-ptr/data/sql/world/001_ptr_creature_templates.sql"
mysql -u root -p tw_world < "modules/mod-twow-ptr/data/sql/world/002_ptr_vendor_items.sql"
mysql -u root -p tw_world < "modules/mod-twow-ptr/data/sql/world/003_ptr_broadcast_text.sql"
mysql -u root -p tw_world < "modules/mod-twow-ptr/data/sql/world/004_ptr_spawns.sql"
```

**Manual import on Windows (PowerShell)**

Run `Get-Command mysql.exe` first. If it is unavailable, install the MySQL or MariaDB command-line client and add its `bin` directory to the current PowerShell session. Replace the example path below with your installation path. Use `mariadb.exe` in the import commands if that is the client you installed. Run imports in the order shown and stop if any command reports an error. `cmd.exe` handles input redirection so the SQL file reaches the client directly.

```powershell
# Only needed when mysql.exe is installed but missing from PATH
# $env:Path = 'C:\Program Files\MySQL\MySQL Server 8.0\bin;' + $env:Path
cmd.exe /d /c 'mysql.exe -u root -p tw_world < modules\mod-twow-ptr\data\sql\world\001_ptr_creature_templates.sql'
if ($LASTEXITCODE -ne 0) { throw "Module SQL import failed" }
cmd.exe /d /c 'mysql.exe -u root -p tw_world < modules\mod-twow-ptr\data\sql\world\002_ptr_vendor_items.sql'
if ($LASTEXITCODE -ne 0) { throw "Module SQL import failed" }
cmd.exe /d /c 'mysql.exe -u root -p tw_world < modules\mod-twow-ptr\data\sql\world\003_ptr_broadcast_text.sql'
if ($LASTEXITCODE -ne 0) { throw "Module SQL import failed" }
cmd.exe /d /c 'mysql.exe -u root -p tw_world < modules\mod-twow-ptr\data\sql\world\004_ptr_spawns.sql'
if ($LASTEXITCODE -ne 0) { throw "Module SQL import failed" }
```

### 4. Deploy and enable the configuration

Create `mod-twow-ptr.conf` inside the `modules/` subdirectory beside the active `mangosd.conf`. For a first install using the example staging directory, the following commands copy the shipped template. If an active module config already exists, retain it and merge new settings from the template.

**Linux**

```bash
mkdir -p server-stage/etc/modules
cp -n "modules/mod-twow-ptr/conf/mod-twow-ptr.conf.dist" "server-stage/etc/modules/mod-twow-ptr.conf"
```

**Windows (PowerShell)**

```powershell
New-Item -ItemType Directory -Force 'server-stage/modules' | Out-Null
if (-not (Test-Path 'server-stage/modules/mod-twow-ptr.conf')) {
    Copy-Item 'modules/mod-twow-ptr/conf/mod-twow-ptr.conf.dist' 'server-stage/modules/mod-twow-ptr.conf'
}
```

Keep the template's section header and confirm `PTR.Enable = 1` in the active file. Start the rebuilt server with your normal launcher and active `mangosd.conf`. Check the startup log for module configuration, database, and dependency errors.

### Verify the installation

Use a test realm. Confirm the PTR Master and vendor are present at a configured spawn or test `.ptr spawn` with an authorized account.

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
