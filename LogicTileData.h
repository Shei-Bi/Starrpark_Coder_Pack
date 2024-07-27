#ifndef LOGICTILEDATA_H
#define LOGICTILEDATA_H

#include "Hook.h"
#include"LogicData.h"

class LogicTileData : public LogicData
{
public:
    unsigned char getTileCode() {
        return ((unsigned char (*)(LogicTileData*))(base + 0x87C8FC))(this);
    }
    int getDamage() {
        return ((int (*)(LogicTileData*))(base + 0x87C978))(this);
    }
    int getSpeedChange() {
        return ((int (*)(LogicTileData*))(base + 0x87C988))(this);
    }
    bool hasWindAnim() {
        return ((bool (*)(LogicTileData*))(base + 0x87CA38))(this);
    }
    bool hidesHero() {
        return ((bool (*)(LogicTileData*))(base + 0x87C968))(this);
    }
    bool blocksMovement() {
        return ((bool (*)(LogicTileData*))(base + 0x87C930))(this);
    }
    bool blocksProjectiles() {
        return ((bool (*)(LogicTileData*))(base + 0x87C938))(this);
    }
    bool isDestructibleWithPiercing() {
        return ((bool (*)(LogicTileData*))(base + 0x87C940))(this);
    }
    bool isDestructibleAny() {
        return ((bool (*)(LogicTileData*))(base + 0x87C948))(this);
    }
};

#endif