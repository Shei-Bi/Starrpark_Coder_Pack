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
        return *(int*)((char*)this + 156);
    }
    int getCustomValue() {
        return *(int*)((char*)this + 168);
    }
    int getCustomValue2() {
        return *(int*)((char*)this + 172);
    }
    int getDamage() {
        return *(int*)((char*)this + 160);
    }
};
#endif