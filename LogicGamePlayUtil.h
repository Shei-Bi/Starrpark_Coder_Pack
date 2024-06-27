#ifndef LOGICGAMEPLAYUTIL_H
#define LOGICGAMEPLAYUTIL_H
#include "Hook.h"
#include "LogicCharacterServer.h"
#include "LogicCharacterData.h"
#include "LogicMath.h"
#include "LogicTileMap.h"
#include "LogicVector2.h"

class LogicGamePlayUtil
{
public:
	static bool canUseFastTravel(LogicCharacterServer* character) {
		if (!character) return false;
		if (((LogicCharacterData*)character->getData())->isHero()) return true;
		return character->isPet();
	}
	static int getDistanceBetween(int x1, int y1, int x2, int y2) {
		return LogicMath::sqrt(((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
	}
	static int calculatePercentDamage(int percent, int damage, bool useMaxHealth, int damageBuff, int damageNerf, int miniumDamage, LogicCharacterServer* target) {
		return ((int (*)(int, int, bool, int, int, int, LogicCharacterServer*))(base + 0x97990C))(percent, damage, useMaxHealth, damageBuff, damageNerf, miniumDamage, target);
	}
	static bool getClosestAnyCollision(int startX, int startY, int endX, int endY, LogicTileMap* tileMap, LogicVector2* outVector, bool a, bool b, bool c, bool d) {
		return ((bool (*)(int, int, int, int, LogicTileMap*, LogicVector2*, bool, bool, bool, bool))(base + 0x9744C0))(startX, startY, endX, endY, tileMap, outVector, a, b, c, d);
	}
};
#endif