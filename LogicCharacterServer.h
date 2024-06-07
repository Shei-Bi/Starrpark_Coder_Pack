#ifndef LCS_H
#define LCS_H
#include "LogicGameObjectServer.h"
#include "LogicArrayList.h"
#include "LogicSkillData.h"
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
	void addConsumableShield(int);
	void tick();
	int getCardValueForPassive(int, int);
	LogicSkillData* getCurrentCastingSkill();
	void interruptAllSkills(bool);
	void stopMovement();
};
#endif