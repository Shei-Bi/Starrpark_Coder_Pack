#ifndef LCS_H
#define LCS_H
#include "LogicGameObjectServer.h"
#include "LogicArrayList.h"
#include "LogicSkillData.h"
#include "LogicCharacterData.h"
#include "LogicData.h"
#include "LogicHeroUpgrades.h"
#include "LogicItemData.h"
#include "LogicVector2.h"
#include "LogicPathFinder.h"
#include "LogicAreaEffectData.h"
#include "BitStream.h"

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
	int AttackAngle;//80
	char gap6[128 - 80 - 4];
	int State;//128
	char gap22[152 - 128 - 4];
	LogicArrayList<int> PathPointsX;//152
	LogicArrayList<int> PathPointsY;//168
	int Hitpoints;//184
	int HitpointsMax;//188
	char gap18[272 - 188 - 4];
	int Pathlength;//272
	char gap1[328 - 272 - 4];
	int AttackAnimation;//328
	char gap23[336 - 328 - 4];
	LogicArrayList<LogicSkillServer*> Skills;//336
	char gap14[8];
	bool Charging;//360
	bool Knockbacked;//361
	char gap16[2];
	bool Stunned;//364
	bool WeaklyStunned;//365
	char gap15[2];
	int StunTicks;//368
	char gap11[4];
	int ShieldTicks;//376
	int ReloadBuffTicks;//380
	int ReloadBuffPercent;//384
	char gap19[440 - 384 - 4];
	int SpawnedTicks;//440
	int SpawnTick;//444
	int CastingTime;//448
	int ChargeDamage;//452
	int ChargeDamageConst;//456
	int ChargePercentDamage;//460
	int ChargePushback;//464
	int ChargeType;//468
	int ChargeChainDistance;//472
	int ChargeAnimation;//476
	int ChargeEndAreaEffectDamage;//480
	int ChargeEndAreaEffectDamageConst;//484
	int DamagedTick;//488
	int PickedItemTick;//492
	int PrepareAttackTick;//496
	int TravelSpeed;//500
	int ChargeUNK2;//504
	int ChargeUNK3;//508
	LogicAreaEffectData* ChargeEndAreaEffect;//512
	char gap13[733 - 512 - 8];
	bool UsingUlti;//733
	char gap20[776 - 733 - 1];
	int StaticSpeedBuff;//776
	int CoinsHeld;//780
	int DestructAfterTicks;//784
	int MinionDamage;//788
	bool IsSpecialMinion;//792
	bool HasReloadBuff;//793;
	char gap4[976 - 793 - 1];
	int HealthRegenBlockedTick;//976
	char gap8[152 - 4];
	LogicArrayList<LogicBuffServer*> Buffs;//1128
	char gap7[1200 - 1128 - 16];
	int ProjectileEffectId;//1200
	int SkinEffectId;//1204
	char gap24[1264 - 1204 - 4];
	bool IsObject;//1264
	char gap21[1284 - 1264 - 1];
	int ShieldPercent;//1284
	char gap12[168 - 140 - 4];
	int ChargeUp;//1312
	char gap5[12];
	int ChargeUpType;
	int ChargeUpMax;
	char gap2[1380 - 336 - 12 - 12 + 8 + 1380 - 2368 + 4];
	int ForcedAngleEndTick;//1380
	char gap17[20];
	int ChargeHits;//1404?
	char gap9[1664 - 1380 - 4 - 24];
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
	void giveSpeedFasterBuff(int, int, bool);
	int getBuffBoost(int);
	void triggerCharge(int, int, int, int, int, int, bool, int, LogicAreaEffectData*, LogicItemData*, int, int, int, bool, LogicArrayList<LogicVector2*>*, LogicAreaEffectData*);
	void ensurePathOk(LogicPathFinder*);
	int getPathLength();
	void chargeTo(int, int, int, LogicPathFinder*, LogicArrayList<LogicVector2*>*);
	void moveTo(int, int, bool, int, bool, bool);
	void addShield(int, int);
	void clearPath();
	void giveReloadBuff(int, int);
	void encode(BitStream*, bool, int, int, bool);
	bool isPlayerControlRemoved();
};
#endif