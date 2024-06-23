#ifndef LOGICAREAEFFECTSERVER_H
#define LOGICAREAEFFECTSERVER_H

#include "LogicGameObjectServer.h"
#include "LogicBattleModeServer.h"
#include "Hook.h"
#include "LogicCharacterServer.h"
class LogicAreaEffectServer : public LogicGameObjectServer
{
public:
	char gap1[96 - 72];
	int Damage;//96
	int DamageConst;//100
	int DamageOverTime;//104
	void setSource(LogicCharacterServer* source, int skillType, bool idk) {
		return ((void (*)(LogicAreaEffectServer*, LogicCharacterServer*, int, int))(base + 0x87E78C))(this, source, skillType, idk);
	}
	void trigger() {
		return ((void (*)(LogicAreaEffectServer*))(base + 0x87E7A0))(this);
	}
};
#endif