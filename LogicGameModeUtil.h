#ifndef LOGICGAMEMODEUTIL_H
#define LOGICGAMEMODEUTIL_H
#include "Hook.h"

class LogicGameModeUtil
{
public:
	static bool playersCollectBountyStars(int mode) {
		return mode == 3 || mode == 15;
	}
	static bool hasSpawnProtectionInTheStart(int mode) {
		if ((mode - 6) > 0x16)
			return false;
		else
			return (0x400309u >> (mode - 6)) & 1;
	}
};
#endif