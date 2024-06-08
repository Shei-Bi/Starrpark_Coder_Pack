#ifndef LCS_H
#define LCS_H
#include "LogicGameObjectServer.h"
#include "LogicArrayList.h"
#include "LogicSkillData.h"
#include "LogicCharacterData.h"
class LogicSkillServer;
class LogicCharacterServer : public LogicGameObjectServer
{
public:
	LogicCharacterServer(LogicCharacterData* logicData) : LogicGameObjectServer(logicData)
	{
		;
	}
	char gap3[4];
	int MoveAngle;
	int ShootAngle;
	char gap1[336 - 72 - 12];
	LogicArrayList<LogicSkillServer*> Skills;
	char gap4[1312 - 336 - 12 - 4];
	int ChargeUp;
	char gap5[12];
	int ChargeUpType;
	int ChargeUpMax;
	char gap2[1380 - 336 - 12 - 12 + 8 + 1380 - 2368 + 4];

	int ForcedAngleEndTick;
	void addConsumableShield(int);
	void tick();
	int getCardValueForPassive(int, int);
	LogicSkillData* getCurrentCastingSkill();
	void interruptAllSkills(bool);
	void stopMovement();
	int getMoveAngle();
	void setForcedAngle(int angle);
	void calculateChargeUp();
};
#endif