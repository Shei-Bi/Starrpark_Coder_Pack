#ifndef LOGICCHARACTERDATA_H
#define LOGICCHARACTERDATA_H
#include "Hook.h"
#include"LogicData.h"
#include "LogicAreaEffectData.h"
#include "LogicSkillData.h"

class LogicCharacterData : public LogicData
{
public:
	char gap3[160];
	LogicAreaEffectData* AreaEffect;//160
	char gap1[492 - 160 - 8];
	int Type;//492
	char gap4[504 - 492 - 4];
	LogicCharacterData* Pet;//504
	LogicSkillData* WeaponSkill;//512
	LogicSkillData* UltiSkill;//520
	char gap2[528 - 520 - 8];
	bool ShouldEncodePetStatus;//528
	char gap5[544 - 528 - 1];
	bool HasPowerLevels;//544
	bool ManualRotations;//545
	int getCollisionRadius()
	{
		return ((int (*)(LogicCharacterData*))(base + 0x8395DC))(this);
	}
	int getUniqueProperty()
	{
		return ((int (*)(LogicCharacterData*))(base + 0x83A234))(this);
	}
	int getUniquePropertyValue1()
	{
		return ((int (*)(LogicCharacterData*))(base + 0x83A244))(this);
	}
	int getUniquePropertyValue2()
	{
		return ((int (*)(LogicCharacterData*))(base + 0x83A32C))(this);
	}
	bool isHero() {
		return Type == 0;
	}
	bool isTurret() {//guessed
		return Type == 4;
	}
	bool isBoss() {
		return Type == 1 || Type == 16;
	}
	int getSpeed()
	{
		return ((int (*)(LogicCharacterData*))(base + 0x839428))(this);
	}
	bool isTrain() {
		return Type == 13 || Type == 19;
	}
	bool isTrainingDummy() {
		return Type == 7;
	}
	bool isDuplicate() {
		return Type == 18;
	}
	LogicAreaEffectData* getAreaEffect() {
		return AreaEffect;
	}
	int getLifeTimeTicks()
	{
		return ((int (*)(LogicCharacterData*))(base + 0x839454))(this);
	}
	LogicCharacterData* getSpawnedPet()
	{
		return Pet;
	}
	bool isCarryable() {
		return ((bool (*)(LogicCharacterData*))(base + 0x83A028))(this);
	}
	int getHitpoints() {
		return ((int (*)(LogicCharacterData*))(base + 0x839430))(this);
	}
	int getUltiChargeInitial() {
		return ((int (*)(LogicCharacterData*))(base + 0x83948C))(this);
	}
	int getChargeUltiAutomatically() {
		return ((int (*)(LogicCharacterData*))(base + 0x83A19C))(this);
	}
	int getFlyingHeight() {
		return ((int (*)(LogicCharacterData*))(base + 0x83A19C))(this);
	}
	int getAutoAttackDamage() {
		return ((int (*)(LogicCharacterData*))(base + 0x839460))(this);
	}
	int getPetAutoSpawnDelay() {
		return *(int*)((char*)this + 536);
	}
};
#endif