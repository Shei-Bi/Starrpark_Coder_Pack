#ifndef LCS_H
#define LCS_H
#include "LogicArrayList.h"
#include "LogicData.h"
class LogicSkillServer;

class LogicCharacterServer : public LogicGameObjectServer
{
public:
	LogicCharacterServer(LogicData* logicData) : LogicGameObjectServer(logicData)
	{
		;
	}
	char gap1[336 - 72];
	LogicArrayList<LogicSkillServer*> Skills;
	char gap2[1504 - 72 - 336 - 12];
	int ConsumableShield;
	int ConsumableShieldMax;
	void addConsumableShield(int amount)
	{
		ConsumableShield = amount;
		ConsumableShieldMax = amount;
	}
	void tick()
	{
		addConsumableShield(114514);
	}
	int getCardValueForPassive(int type, int index) {
		return -1;
	}
};
#endif