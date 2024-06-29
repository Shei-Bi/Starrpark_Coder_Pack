#ifndef LOGICAREAEFFECTDATA_H
#define LOGICAREAEFFECTDATA_H
#include "Hook.h"
#include "LogicData.h"
class LogicAreaEffectData : public LogicData
{
public:
    char gap1892724[144];
    int Type;

    int getRadius() {
        return ((int (*)(LogicAreaEffectData*))(base + 0x82D998))(this);
    }
    int getCustomValue2() {
        return ((int (*)(LogicAreaEffectData*))(base + 0x82D9B0))(this);
    }
};
#endif