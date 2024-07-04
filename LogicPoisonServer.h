#ifndef LOGICPOISONSERVER_H
#define LOGICPOISONSERVER_H
#include "LogicCharacterServer.h"
#include "LogicData.h"
class LogicPoisonServer
{
public:
    int EffectTimer;// *
    int EffectTimes;//4
    int Damage;//8
    int DamageConst;//12
    LogicCharacterServer* Source;//16
    int Index;//24
    int Type;//28
    bool IsUlti;//32
    bool ShouldDestruct;//33

    enum PoisonTypes//guessed names 
    {
        Poison = 1,
        Fire = 2,
        Electronic = 3,
        SnakeOil = 4,
        CrowSuper = 5,
        JesterSmoke = 7,
        WillowPoison = 9
    };
    LogicPoisonServer(int damage, int damageConst, int effectTimes, bool isUlti, LogicCharacterServer* source, int index, int type) {
        EffectTimer = 20;
        EffectTimes = effectTimes;
        Damage = damage / effectTimes;
        DamageConst = damageConst / effectTimes;
        Source = source;
        Index = index;
        Type = type;
        isUlti = isUlti;
        ShouldDestruct = false;
        if (type == WillowPoison) EffectTimer = 0;
    }
    bool tick(LogicCharacterServer* character) {
        if (ShouldDestruct) return true;
        if (--EffectTimer > 0) return false;
        character->causeDamage(Index, Damage, DamageConst, Source, true, 0, 0, nullptr, true, IsUlti, false, true, false, Type == WillowPoison);
        EffectTimer = 20;
        EffectTimes--;
        if (!EffectTimes) return true;
        return false;
    }
    void refreshPoison(int type, int damage, int damageConst, int effectTimes, bool isUlti) {
        Type = type;
        EffectTimes = effectTimes;
        Damage = damage / effectTimes;
        DamageConst = damageConst / effectTimes;
        IsUlti = isUlti;
    }
    static int getTickCount(int type) {
        if (type == SnakeOil) return 2;
        return 4;
    }
    static bool allowStacking(int type) {
        return type == SnakeOil || type == WillowPoison;
    }
};
#endif