#ifndef LCS_H
#define LCS_H
#include "LogicGameObjectServer.h"
#include "LogicArrayList.h"
#include "LogicSkillData.h"
#include "LogicCharacterData.h"
#include "LogicData.h"
#include "LogicHeroUpgrades.h"

class LogicSkillServer;
class LogicBuffServer;
class LogicGear;
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
	char gap4[1128 - 336 - 12 - 4 - 152];
	int HealthRegenBlockedTick;//976
	char gap8[152 - 4];
	LogicArrayList<LogicBuffServer*> Buffs;//1128
	char gap7[168];
	int ChargeUp;//1312
	char gap5[12];
	int ChargeUpType;
	int ChargeUpMax;
	char gap2[1380 - 336 - 12 - 12 + 8 + 1380 - 2368 + 4];
	int ForcedAngleEndTick;//1380
	char gap9[1664 - 1380 - 4];
	LogicArrayList<LogicGear*> Gears;

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
	void blockHealthRegen();
	void tickEffects();
	void tickGears();//guessed name
	void tickStarPowers();
	void setUpgrades(LogicHeroUpgrades*);
	void applyBuff(int, int, int, int);
	void giveDamageBuff(int, int);
	int getDamageBuffTemporary();
};
#endif