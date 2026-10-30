#ifndef _PTR_MASTER_NPC_H_
#define _PTR_MASTER_NPC_H_

#include "ScriptObjects.h"
#include "ScriptedAI.h"

class ptr_master_npc : public CreatureScript
{
public:
    ptr_master_npc();

    bool OnGossipHello(Player* player, Creature* creature) override;
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override;
    CreatureAI* GetAI(Creature* creature) const override;
};

void AddPTRMasterNPCScripts();

#endif
