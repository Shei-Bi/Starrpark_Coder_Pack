#include "LogicGameObjectServer.h"
#include "LogicCharacterServer.h"
int main()
{
    // LogicGameObjectServer l[2];
    // l[0] = new LogicCharacterServer();
    // l[0].tick();
    LogicGameObjectServer e = LogicGameObjectServer();
    e = LogicCharacterServer();
    e.tick();
};