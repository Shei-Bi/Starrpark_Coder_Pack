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
	int SkillHoldAngle;//84
	char gap6[128 - 84 - 4];
	int State;//128
	char gap22[152 - 128 - 4];
	LogicArrayList<int> PathPointsX;//152
	LogicArrayList<int> PathPointsY;//168
	int Hitpoints;//184
	int HitpointsMax;//188
	char gap18[268 - 188 - 4];
	bool AttackChargedUp;//268
	char gap34[272 - 268 - 1];
	int Pathlength;//272
	char gap1[296 - 272 - 4];
	bool IsInvincible;//296
	bool IsTeleporting;//297
	char gap31[328 - 297 - 1];
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
	char gap36[996 - 976 - 4];
	int Size;//996
	char gap8[1088 - 996 - 4];
	bool BotMovingFlag;//1088
	bool AimingUlti;//1089
	bool BotAimingUlti;//1090
	bool ShowUltiAnimation;//1091
	int BattleRoyalBuffs;//1092
	char gap29[1128 - 1092 - 4];
	LogicArrayList<LogicBuffServer*> Buffs;//1128
	char gap35[1156 - 1128 - 16];
	bool IsHyperchargeMinion;//1156
	char gap7[1200 - 1156 - 1];
	int ProjectileEffectId;//1200
	int SkinEffectId;//1204
	char gap24[1213 - 1204 - 4];
	bool ShowStarPowerIcon;//1213
	char gap27[1264 - 1213 - 1];
	bool IsObject;//1264
	char gap32[1272 - 1264 - 1];
	int ChargedShotCount;//1272
	char gap21[1284 - 1272 - 4];
	int ShieldPercent;//1284
	char gap28[1292 - 1284 - 4];
	int LifeTimeTicks;//1292
	char gap12[1312 - 1292 - 4];
	int ChargeUp;//1312
	char gap5[12];
	int ChargeUpType;
	int ChargeUpMax;
	char gap2[1380 - 336 - 12 - 12 + 8 + 1380 - 2368 + 4];
	int ForcedAngleEndTick;//1380
	char gap17[1404 - 1380 - 4];
	int ChargeHits;//1404?
	char gap25[1452 - 1404 - 4];
	bool IsSlippery;//1452
	int PartialStunPromille;//1456
	int PartialStunDecrementTimer;//1460
	int PartialStunnedTicks;//1464
	char gap30[1473 - 1464 - 4];
	bool HasRuffsBuff;//1473
	char gap26[1504 - 1473 - 1];
	int ConsumableShield;//1504
	int ConsumableShieldMax;//1508
	char gap33[1532 - 1508 - 4];
	int SkillHoldTicks;//1532
	char gap9[1664 - 1532 - 4];
	LogicArrayList<LogicGear*> Gears;//1664

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
	void setPartialStunPromille(int);
	void giveSlipperyDebuff();
	void triggerStun(int, bool);
	LogicBuffServer* findBuffByType(int);
	bool isPet();
};
#endif