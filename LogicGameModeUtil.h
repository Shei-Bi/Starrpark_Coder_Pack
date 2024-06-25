#ifndef LOGICGAMEMODEUTIL_H
#define LOGICGAMEMODEUTIL_H
#include "Hook.h"

class LogicGameModeUtil
{
public:
	static bool playersCollectBountyStars(int mode) {
		return mode == 3 || mode == 15;
	}
};
#endif