#ifndef LOGICCARDDATA_H
#define LOGICCARDDATA_H
#include "Hook.h"
#include "LogicData.h"
class LogicCardData : public LogicData
{
public:
    char gap1[136];
    int Value; //136
    int Value2; //140
    int getValue() {
        return Value;
    }
    int getValue2() {
        return Value2;
    }
    int getType() {
        return *(int*)((char*)this + 120);
    }
};
#endif