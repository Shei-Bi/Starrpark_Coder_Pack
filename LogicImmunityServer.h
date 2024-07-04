#ifndef LOGICIMMUNITYSERVER_H
#define LOGICIMMUNITYSERVER_H

#include "LogicData.h"
class LogicImmunityServer
{
public:
    int Index;
    int Ticks;
    LogicData* Type;

    LogicImmunityServer(int index, LogicData* type, int ticks) {
        Index = index;
        Type = type;
        Ticks = ticks;
    }
};
#endif