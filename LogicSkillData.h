#ifndef LSD_H
#define LSD_H
#include "Hook.h"
#include"LogicData.h"
#include "LogicProjectileData.h"

class LogicSkillData : public LogicData
{
public:
	char gap3[88];
	LogicProjectileData* Projectile;//88
	char gap1[340 - 88 - 8];
	int BehaviorType;
	char gap2[356 - 340 - 4];
	bool HoldToShoot;
	int getMaxCharge()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873D40))(this);
	}
	int getCastingTime()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873BB4))(this);
	}
	int getChargeSpeed()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873B5C))(this);
	}
	int getChargeType()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873D20))(this);
	}
	int getActiveTime()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873B8C))(this);
	}
	int getChargedShotCount()
	{
		return ((int (*)(LogicSkillData*))(base + 0x874124))(this);
	}
	int getAttackPattern()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873E10))(this);
	}
	LogicProjectileData* getProjectile()
	{
		return Projectile;
	}
	int getSkillChangeType()
	{
		return ((int (*)(LogicSkillData*))(base + 0x874094))(this);
	}
	bool skillCanChange() {
		return ((bool (*)(LogicSkillData*))(base + 0x87406C))(this);
	}
	int getDamage() {
		return ((int (*)(LogicSkillData*))(base + 0x873D48))(this);
	}
};
#endif