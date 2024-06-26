#ifndef LOGICCARDDATA_H
#define LOGICCARDDATA_H
#include "Hook.h"
#include "LogicData.h"
class LogicCardData : public LogicData
{
public:
    char gap1[136];
    int Value; //136
    int getValue() {
        return Value;
    }
};
#endif