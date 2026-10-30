#ifndef _PTR_VENDOR_NPC_H_
#define _PTR_VENDOR_NPC_H_

#include "ScriptObjects.h"
#include "ScriptedAI.h"

class ptr_vendor_npc : public CreatureScript
{
public:
    ptr_vendor_npc();

    CreatureAI* GetAI(Creature* creature) const override;
};

void AddPTRVendorNPCScripts();

#endif
