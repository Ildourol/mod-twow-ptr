#ifndef _PTR_LOOT_HELPER_H_
#define _PTR_LOOT_HELPER_H_

#include "ScriptObjects.h"
#include "ScriptedAI.h"

class ptr_loot_helperAI : public ScriptedAI
{
public:
    explicit ptr_loot_helperAI(Creature* creature);

    uint32_t GetCreatureEntry() const { return m_lootEntry; }
    void SetCreatureEntry(uint32_t entry) { m_lootEntry = entry; }

    bool IsVisibleToPlayers() const { return m_visibleToPlayers; }
    void SetPlayerVisibility(bool visible);

    void Reset() override;

private:
    uint32_t m_lootEntry{ 0 };
    bool m_visibleToPlayers{ false };
};

class ptr_loot_helper : public CreatureScript
{
public:
    ptr_loot_helper();

    bool OnGossipHello(Player* player, Creature* creature) override;
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override;
    CreatureAI* GetAI(Creature* creature) const override;
};

void AddPTRLootHelperScripts();

#endif
