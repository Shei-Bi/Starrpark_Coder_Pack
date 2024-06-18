#ifndef LCS_H
#define LCS_H
#include "LogicGameObjectServer.h"
#include "LogicArrayList.h"
#include "LogicSkillData.h"
#include "LogicCharacterData.h"
#include "LogicBuffServer.h"
#include "LogicData.h"

class LogicSkillServer;
class LogicCharacterServer : public LogicGameObjectServer
{
public:
	LogicCharacterServer(LogicCharacterData* logicData) : LogicGameObjectServer(logicData)
	{
		;
	}
	char gap3[4];
	int MoveAngle;//76
	int ShootAngle;//80
	char gap6[100];
	int Hitpoints;//184
	int HitpointsMax;//188
	char gap1[336 - 72 - 12 - 100 - 8];
	LogicArrayList<LogicSkillServer*> Skills;//336
	char gap4[1128 - 336 - 12 - 4];
	LogicArrayList<LogicBuffServer*> Buffs;//1128
	char gap7[168];
	int ChargeUp;//1312
	char gap5[12];
	int ChargeUpType;
	int ChargeUpMax;
	char gap2[1380 - 336 - 12 - 12 + 8 + 1380 - 2368 + 4];
	int ForcedAngleEndTick;//1380

	void addConsumableShield(int);
	void tick();
	int getCardValueForPassive(int, int);
	LogicSkillData* getCurrentCastingSkill();
	void interruptAllSkills(bool);
	void stopMovement();
	int getMoveAngle();
	void setForcedAngle(int angle);
	void calculateChargeUp();
	int heal(int, int, bool, LogicData*);
	void addExtraHealthRegen(int, int, int, LogicData*);
};
#endif