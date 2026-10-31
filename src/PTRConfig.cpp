#include "PTRConfig.h"
#include "Config/Config.h"
#include "Log.h"

PTRConfig& PTRConfig::Instance()
{
    static PTRConfig instance;
    return instance;
}

void PTRConfig::Load()
{
    m_enabled              = sConfig.GetBoolDefault("PTR.Enable", true);
    m_gmOnly               = sConfig.GetBoolDefault("PTR.GMOnly", false);
    m_goldAmount           = static_cast<uint32_t>(sConfig.GetIntDefault("PTR.GoldAmount", 10000000));
    m_giveBags             = sConfig.GetBoolDefault("PTR.GiveBags", true);
    m_maxSkills            = sConfig.GetBoolDefault("PTR.MaxSkills", true);
    m_maxRidingSkills      = sConfig.GetBoolDefault("PTR.MaxRidingSkills", true);
    m_giveMountItem        = sConfig.GetBoolDefault("PTR.GiveMountItem", true);
    m_teachClassSpells     = sConfig.GetBoolDefault("PTR.TeachClassSpells", true);
    m_autoEnchantBiS       = sConfig.GetBoolDefault("PTR.AutoEnchantBiS", true);
    m_grantAttunements     = sConfig.GetBoolDefault("PTR.GrantAttunements", true);
    m_maxRaidReputations   = sConfig.GetBoolDefault("PTR.MaxRaidReputations", true);
    m_requireFullRaidGroup = sConfig.GetBoolDefault("PTR.RaidTeleport.RequireFullGroup", false);
    m_lootHelperEnabled    = sConfig.GetBoolDefault("PTR.LootHelper.Enabled", true);
    m_lootHelperGMOnly     = sConfig.GetBoolDefault("PTR.LootHelper.GMOnly", true);

    sLog.outString(">> [mod-twow-ptr] Config loaded: Enabled=%d, GMOnly=%d, Gold=%u, MaxSkills=%d, MaxRidingSkills=%d, AutoEnchant=%d, LootHelper=%d",
        m_enabled ? 1 : 0, m_gmOnly ? 1 : 0, m_goldAmount, m_maxSkills ? 1 : 0, m_maxRidingSkills ? 1 : 0, m_autoEnchantBiS ? 1 : 0, m_lootHelperEnabled ? 1 : 0);
}
