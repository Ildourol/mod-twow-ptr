#include "ScriptObjects.h"
#include "Log.h"
#include "PTRConfig.h"

void AddPTRMasterNPCScripts();
void AddPTRVendorNPCScripts();
void AddPTRLootHelperScripts();
void AddPTRCommandScripts();

namespace
{
    class ModTwowPTRWorldScript : public WorldScript
    {
    public:
        ModTwowPTRWorldScript()
            : WorldScript("mod-twow-ptr_world", { WORLDHOOK_ON_STARTUP })
        {
        }

        void OnStartup() override
        {
            sPTRConfig.Load();
            sLog.outString(">> [mod-twow-ptr] Testing Hub & Raid BIS Gearing initialized successfully.");
        }
    };
}

void Addmod_twow_ptrScripts()
{
    new ModTwowPTRWorldScript();
    AddPTRMasterNPCScripts();
    AddPTRVendorNPCScripts();
    AddPTRLootHelperScripts();
    AddPTRCommandScripts();
}

// Canonical catalog alias loader
void Addmod_twow_ptr_masterScripts()
{
    Addmod_twow_ptrScripts();
}
