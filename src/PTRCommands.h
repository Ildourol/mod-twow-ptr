#ifndef _PTR_COMMANDS_H_
#define _PTR_COMMANDS_H_

#include "ScriptObjects.h"

class PTRCommandScript : public AllCommandScript
{
public:
    PTRCommandScript();

    bool CanExecuteCommand(ChatHandler* handler, char const* cmd, char const* argsIn) override;
};

void AddPTRCommandScripts();

#endif
