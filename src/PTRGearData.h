#ifndef _PTR_GEAR_DATA_H_
#define _PTR_GEAR_DATA_H_

#include "PTRCommon.h"

namespace PTRGearData
{
    // Returns full vector of (ClassesAndRoles, BiS Items, Weapon Spells)
    std::vector<std::tuple<ClassesAndRoles, std::list<uint32_t>, std::list<uint32_t>>> const& GetBisItemsAndSpells();

    // Returns world buff spell list
    std::list<uint32_t> const& GetWorldBuffs();

    // Returns raid teleport destinations
    std::vector<RaidLocation> const& GetRaidLocations();

    // Returns class attunement spells
    std::list<uint32_t> const& GetAttunementSpells();

    // Returns optimal PvE permanent enchant ID for an item based on its InventoryType & role
    uint32_t GetOptimalEnchant(uint32_t inventoryType, ClassesAndRoles role);
}

#endif
