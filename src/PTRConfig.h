#ifndef _PTR_CONFIG_H_
#define _PTR_CONFIG_H_

#include <cstdint>

class PTRConfig
{
public:
    static PTRConfig& Instance();

    void Load();

    bool IsEnabled() const { return m_enabled; }
    bool IsGMOnly() const { return m_gmOnly; }
    uint32_t GetGoldAmount() const { return m_goldAmount; }
    bool GiveBags() const { return m_giveBags; }
    bool MaxSkills() const { return m_maxSkills; }
    bool TeachClassSpells() const { return m_teachClassSpells; }
    bool AutoEnchantBiS() const { return m_autoEnchantBiS; }
    bool GrantAttunements() const { return m_grantAttunements; }
    bool MaxRaidReputations() const { return m_maxRaidReputations; }
    bool RequireFullRaidGroup() const { return m_requireFullRaidGroup; }
    bool IsLootHelperEnabled() const { return m_lootHelperEnabled; }
    bool IsLootHelperGMOnly() const { return m_lootHelperGMOnly; }

private:
    PTRConfig() = default;

    bool m_enabled{ true };
    bool m_gmOnly{ false };
    uint32_t m_goldAmount{ 10000000 };
    bool m_giveBags{ true };
    bool m_maxSkills{ true };
    bool m_teachClassSpells{ true };
    bool m_autoEnchantBiS{ true };
    bool m_grantAttunements{ true };
    bool m_maxRaidReputations{ true };
    bool m_requireFullRaidGroup{ false };
    bool m_lootHelperEnabled{ true };
    bool m_lootHelperGMOnly{ true };
};

#define sPTRConfig PTRConfig::Instance()

#endif
