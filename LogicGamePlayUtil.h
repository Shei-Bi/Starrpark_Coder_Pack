#ifndef LOGICGAMEPLAYUTIL_H
#define LOGICGAMEPLAYUTIL_H
#include "Hook.h"
#include "LogicCharacterServer.h"
#include "LogicCharacterData.h"

class LogicGamePlayUtil
{
public:
	static bool canUseFastTravel(LogicCharacterServer* character) {
		if (!character) return false;
		if (((LogicCharacterData*)character->getData())->isHero()) return true;
		return character->isPet();
	}
};
#endif