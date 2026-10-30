#include "PTRVendorNPC.h"
#include "PTRConfig.h"

struct ptr_vendor_npcAI : public ScriptedAI
{
    explicit ptr_vendor_npcAI(Creature* creature) : ScriptedAI(creature)
    {
        ptr_vendor_npcAI::Reset();
    }

    void Reset() override
    {
        if (sPTRConfig.IsEnabled())
            m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
        else
            m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);

        m_creature->AddUnitState(UNIT_STAT_ROOT);
    }

    void UpdateAI(uint32 const /*uiDiff*/) override
    {
        if (!sPTRConfig.IsEnabled() && m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR))
            m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
        else if (sPTRConfig.IsEnabled() && !m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR))
            m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
    }
};

ptr_vendor_npc::ptr_vendor_npc()
    : CreatureScript("ptr_vendor_npc")
{
}

CreatureAI* ptr_vendor_npc::GetAI(Creature* creature) const
{
    return new ptr_vendor_npcAI(creature);
}

void AddPTRVendorNPCScripts()
{
    new ptr_vendor_npc();
}
