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
#include "String.h"
#include "LogicDataSlot.h"
#include "LogicImmunityServer.h"

class LogicSkillServer;
class LogicBuffServer;
class LogicGear;
class LogicPoisonServer;
class LogicCharacterServer : public LogicGameObjectServer
{
public:
	LogicCharacterServer(LogicCharacterData* logicData) : LogicGameObjectServer(logicData)
	{
		;
	}
	int MoveAngle;//76
	int AttackAngle;//80
	int SkillHoldAngle;//84
	LogicVector2 TempVector1;//88
	LogicVector2 TempVector2;//96
	LogicVector2 TempVector3;//104
	LogicVector2 TempVector4;//112
	LogicVector2 TempVector5;//120
	int State;//128
	int RapidFireLastAttackedTick;//132
	int RapidFireLastAttackedTickAdd2;//136 (????)
	char gap8986786488[4];//140
	int MinionIdleAnimationTimer;//144 (when reaching 700,has 50% chance to turn to random angle)
	char gap1497314978[4];//148
	LogicArrayList<int> PathPointsX;//152
	LogicArrayList<int> PathPointsY;//168
	int Hitpoints;//184
	int HitpointsMax;//188
	int HitpointsMaxOriginal;//192
	int RapidFireDamage;//196
	int RapidFireShootTimes;//200 (= ActiveTime / MsBetweenAttacks)
	int RapidFireShootIndex;//204
	bool RapidFireWeaponCounter;//208 (false = left hand)
	int RapidFireProjectileSpecialEffect;//212 (for lola 1st sp)
	int RapidFireDamageConst;//216
	int RapidFireAttackPattern;//220
	int RapidFireNumBulletsInOneAttack;//224
	char gap41938479387[4];
	LogicProjectileData* RapidFireProjectile;//232
	int RapidFireSpread;//240
	int RapidFireMsBetweenAttacks;//244
	int RapidFireRange;//248
	char gap198472047[4];//252
	LogicVector2 RapidFireAttackPosition;//256
	int RapidFireExtraRange;//264
	bool AttackChargedUp;//268
	int Pathlength;//272
	char gap10384384034[4];//276
	int ParentGID;//280
	int LastHealthRegenTick;//284
	int LastAILogicTick;//288
	int ScheduledAILogicTick;//292
	bool IsInvincible;//296
	bool IsTeleporting;//297
	bool gap31973827;//298
	bool SamHasWeapon;//299
	int BlinkX;//300
	int BlinkY;//304
	char gap31[4];
	int GiantGrowthTicks;//312
	int RadioactiveGlowEndTick;//316
	int ToxicFumesDamageEndTick;//320
	int ToxicFumesDamageIncrease;//324
	int AttackAnimation;//328
	char gap23[4];
	LogicArrayList<LogicSkillServer*> Skills;//336
	bool RapidFireTwoGuns;//352
	bool IsBot;//353
	int DamageBuffPermanent;//356
	bool Charging;//360
	bool Knockbacked;//361
	bool KnockbackedAndCanNotActivateCcImmunityGadget;//362
	bool KnockbackedBackwards;//true for passive knockbacks, false for offensive knockbacks, true for Janet 2nd gadget
	bool Stunned;//364
	bool WeaklyStunned;//365
	int StunTicks;//368
	int ShakeTicks;//372
	int ShieldTicks;//376
	int ReloadBuffTicks;//380 unused
	LogicArrayList<int> ChargeDamageImmunitys_GlobalID;//384
	LogicArrayList<int> ChargeDamageImmunitys_Timer;//400
	LogicCharacterServer* AutoAttackTarget;//416
	int AutoAttackX;//424
	int AutoAttackY;//428
	bool HasAutoAttackTarget;//432
	bool BotUnknownBoolean1;//433
	int BotArtTestUnknownInt1;//436
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
	char AttackSpecialParams[720 - 512 - 8];
	int InvisibleTicks;//720
	bool IsInvisible;//724
	bool IsRevealed;//725
	int InvisibilityState;//728
	bool NoAI;//732
	bool UsingUlti;//733
	int JanetTargetMoveAngle;//736
	int JanetActualMoveAngle;//740
	int BurstAutoAttackModeAttackTimer;//744
	int BurstAutoAttackModeBulletsShoot;//748
	int BurstAutoAttackModeDamage;//752
	int BurstAutoAttackModeDamageConst;//756
	LogicVector2 BurstAutoAttackModePosition;//760 (?)
	int AoeRegenerateHeal;//768
	int AoeRegenerateInterval;//772 (Shall be unused)
	int StaticSpeedBuff;//776
	int CoinsHeld;//780
	int DestructAfterTicks;//784
	int MinionDamage;//788
	bool IsSpecialMinion;//792
	bool HasReloadBuff;//793;
	bool HasCharacterBuffingVariables;//794
	bool IsPushbackedAndCanNotTakeHits;//795
	bool IsGrappled;//796
	bool IsPushbackedAndCanNotBePushbacked;//797
	int ProjectileDataKickback;//800 (????????)
	int CripplePercent;//804
	int CrippleEndTick;//808
	bool Crippled;//812
	int AutoUltiChargeTimer;//816
	char BotVariables[904 - 816 - 4];
	LogicArrayList<int> DamageNumbers_Value;//904
	LogicArrayList<int> DamageNumbers_Index;//920
	LogicArrayList<int> DamageNumbers_Delay;//936
	LogicArrayList <LogicDataSlot*> Starpowers;//952
	LogicAreaEffectServer* AreaEffect;//968
	int HealthRegenBlockedTick;//976
	int SpawnMinionTimer;//980
	int TicksSinceLastMinionSpawn;//984 (for encode)
	int DelayedDeathTicks;//988
	int DamagedFromAngle;//992 (for encode)
	int Size;//996 
	int RoboWarsRoboLevel;//1000
	char gap938493849[4];//1004
	LogicSkillData* ChesterNextUlti;//1008
	LogicCharacterServer* Carryable;//1016
	char gap8[1056 - 1016 - 8];
	int CarryableLastOwnerPlayerIndex;//1056
	int CarryableUnkownInt1;//1060
	int CarryableUnkownInt2;//1064
	bool CarryableUnkownBoolean;//1068
	LogicVector2 VectorUnknownUnused1;//1072
	LogicVector2 VectorUnknownUnused2;//1080
	bool BotMovingFlag;//1088
	bool AimingUlti;//1089
	bool BotAimingUlti;//1090
	bool ShowUltiAnimation;//1091
	int BattleRoyalBuffs;//1092
	LogicArrayList<LogicPoisonServer*> Poisons;//1096
	LogicArrayList<LogicImmunityServer*> Immunitys;//1112;
	LogicArrayList<LogicBuffServer*> Buffs;//1128
	int LastDamageSourceIndex;//1144
	int MinionMaxHealthBuff;//1148
	int TravelledPathLength;//1152
	bool IsHyperchargeMinion;//1156
	LogicItemData* SummoningItem;//1160
	LogicCharacterData* SummoningCharacter;//1168
	bool SpawningPet;//1176
	bool SummoningCharacterUnknownVariableBoolean;//1177
	int SummoningCharacterNumSpawns;//1180
	int SummoningCharacterMaxSpawns;//1184
	int SummoningCharacterDamage;//1188
	int SummoningItemDamage;//1192
	int SummoningCharacterHitpoints;//1196
	int ProjectileEffectId;//1200
	int SkinEffectId;//1204
	int MinionFollowOwnerTimer;//1208
	bool MinionChargesUlti;//1212
	bool ShowStarPowerIcon;//1213
	char PathfindingVariablesUnused[1232 - 1213 - 1];
	int SummonedBoxOfSelfDestructBombsDamage;//1232
	int BuffVisualStyleTicks;//1236
	int BuffVisualStyle;//1240
	int CarryableAimX;//1244
	int CarryableAimY;//1248
	int CarryableAimTicks;//1252
	bool InvisibilityBreaksWhenAttack;//1256 (这玩意死了四年，到里昂出极冲的时候复活了)
	int InvisibilityRevealDistance;//1260
	bool IsObject;//1264
	int RapidFireLastUpdatedTick;//1268
	int ChargedShotHits;//1272
	int ChargedShotMisses;//1276
	int MaxStarpowerCachedChargeUp;//1280
	int ShieldPercent;//1284
	int CcImmunityTicks;//1288
	int LifeTimeTicks;//1292
	LogicArrayList<int> UnknownUnused;//1296
	int ChargeUp;//1312
	int LastAshChargeUpTick;//1316
	char gap5[8];
	int ChargeUpType;//1328
	int ChargeUpMax;//1332
	char gap1239187943874[8];
	LogicProjectileData* OverrideProjectile;//1344
	LogicProjectileData* OverrideProjectileSecondary;//1352
	int OverrideProjectileEndTick;//1360
	int VisionOverrideX;//1364
	int VisionOverrideY;//1368
	int VisionOverrideTicks;//1372
	int PoisonCloudDamageTimer;//1376
	int ForcedAngleEndTick;//1380
	int TownCrushBossSearchTileTimer;//1384
	char gap103897[4];
	LogicGameObjectServer* DraggingObject;//1392
	int DraggingAngle;//1400
	int ChargeHits;//1404
	bool ForceAILogicNextTick;//1408
	char gap25[1432 - 1408 - 4];
	LogicArrayList<LogicVector2*> PrevPositions; //1432
	int PrevZ;//1448
	bool IsSlippery;//1452
	int PartialStunPromille;//1456
	int PartialStunDecrementTimer;//1460
	int PartialStunnedTicks;//1464
	int StateLockedTicks;//1468 (for Amber, if she don't lock her State for 2 ticks after attacking then walk-attack facing will unpreferable)
	bool LeonCloneVisualHasUlti;//1472
	bool HasRuffsBuff;//1473
	bool DoesNotCountTowardsMaxSpawns;//1474
	int RuffsCooldownTimer;//1476
	LogicVector2 LastTrailAreaPosition;//1480
	LogicCharacterServer* BuzzHookedCharacter;//1488
	LogicVector2 BuzzHookedPosition;//1496
	int ConsumableShield;//1504
	int ConsumableShieldMax;//1508
	int ConsumableShieldTicks;//1512
	int ConsumableShieldTicksMax;//1516
	char gap8914871834[4];//1520
	int UnmovableInvicibleTimer;//1524
	bool IgnoreDeployTime;//1528 (for lolla pet)
	bool DoNotUseDefaultDeathEffect;//1529 (for Meg and Bonnie)
	int SkillHoldTicks;//1532
	char gap397865[4];
	int WillowPuppetingTicks;//1540
	int WillowPuppetingMiniumHitpointPercentage;//1544
	int WillowPuppetingIndex;//1548
	int DougTimer1;//1552
	int DougTimer2;//1556
	int DougIndex;//1560
	int DougTeamIndex;//1564
	int KitAttachingTicks;//1568
	bool KitAttaching;//1572
	int KitAttachingIndex;//1576
	int KitAttachingTeamIndex;//1580
	bool TwimUnknownBoolean;//1584
	int ShadowRealmTicks;//1588
	int ShadowRealmWorldIndex;//1592
	int ShadowRealmTicksMax;//1596
	bool OnEnterShadowRealm;//1600
	bool HasProjectileShieldSkill;//1601
	LogicVector2 MinionInvasionSpawnPosition;//1604
	char gap32989[4];
	LogicArrayList<LogicData*> UNK_AttackSpecialParams;//1616
	LogicArrayList<LogicGameObjectServer*> UNK_Teammates;//1632
	LogicArrayList<LogicVector2*> UNK_Vector2s;//1648
	LogicArrayList<LogicGear*> Gears;//1664

	//crazy guessed names xD
	int SpikeTileDamageTimer;//1680
	int PoisonTileDamageTimer;//1684
	char gap19839289[4];//1688
	int ChesterWeaponCounter;//1692
	LogicCharacterServer* CordeliusStarpowerComboTarget;//1696
	LogicItemServer* ChunkUltiTarget;//1704
	LogicProjectileServer* CharlieYoyo;//1712
	LogicCharacterServer* CharlieCocconLinkedCharacter;//1720
	LogicCharacterServer* KitAttachingCharacter;//1728

	void tickGears();//guessed name
	int getBuffBoost(int);
	LogicBuffServer* findBuffByType(int);
	void triggerPullRope(LogicCharacterServer*);
	void tickDuplicatorAndCocconAndMinionPercenter();
	void tickConductor();
	LogicSkillData* getNextChesterUlti(LogicSkillData*, bool);
	LogicCharacterServer* triggerTransformation(LogicCharacterData*);
	int getDamageForCalculatingCardDamageAfterV52(void);
	LogicGear* getGearBoost(int);

	void AICanRaiseDead(void);
	void AICanResurrect(void);
	void AIactivateAllSkillsOfType(int, LogicSkillData*, LogicSkillData*, LogicSkillData*, int, int, bool, bool, bool, bool, bool);
	void AIthrowBasketball(int, int);
	void AIthrowCaptureFlag(void);
	void AIthrowLaserBall(LogicCharacterServer*, bool);
	void activateSkill(LogicSkillData*, int, int);
	void activateSkill(String const&, int, int);
	void activateSkill(int, int, int);
	void addAreaEffect(int, int, LogicAreaEffectData*, int, bool);
	void addCcImmunity(int);
	void addConsumableShield(int);
	void addExtraHealthRegen(int, int, int, LogicData*);
	void addPoint(int, int);
	void addShield(int, int);
	void addStars(int);
	void aiAddSeenEnemy(LogicCharacterServer*);
	void aiMoveToPreferForest(int, int, bool, bool, bool, bool, bool, bool);
	void aiUpdateSeenEnemies(void);
	void aiUseExploreSkills(void);
	void aiUseMovementSkills(int, int);
	void aiUseOffensiveSkills(LogicCharacterServer*, bool, bool, bool, bool);
	void applyBuff(int, int, int, int);//
	void applyPoison(int, int, int, bool, LogicCharacterServer*, int, int);//
	void attack(LogicCharacterServer*, int, int, int, int, LogicProjectileData*, int, bool, int, int);
	void attackedThisTick(int);
	void blockHealthRegen(void);
	void bossEngageUseSkills(LogicCharacterServer*, LogicCharacterServer*, bool);
	void bossExploreUseSkills(void);
	void bossTownCrusherUseSkills(void);
	void bossUseFirstGroupSkills(LogicCharacterServer*);
	void bossUseSecondGroupSkills(LogicCharacterServer*);
	void buffRoboWarsRobo(int, int, int, int);
	void calculateCarryableWallBounce(bool, int, int, bool);
	void calculateChargeUp(void);
	void calculateDamageBuffsAndNerfs(int);
	void canGrappleTarget(void);
	void canMoveAndUseThisSkillSimultaneously(LogicSkillData*);
	void canTakeHits(void);
	void cancelSkill(void);
	bool causeDamage(int, int, int, LogicCharacterServer*, bool, int, int, LogicData*, bool, bool, bool, bool, bool, bool);
	void chargeTo(int, int, int, LogicPathFinder*, LogicArrayList<LogicVector2*>*);
	void chargeUlti(int, bool, bool, LogicPlayer*, LogicCharacterServer*);
	void clearPath(void);
	void clearSkillList(void);
	void closeToWater(void);
	void cripple(int);
	void destruct(void);
	void dropCarryable(int, int);
	void dropThis(void);
	void encode(BitStream*, bool, int, int, bool);
	void endRapidFire(void);
	void ensurePathOk(LogicPathFinder*);
	void executeBlink(void);
	void executeKickBack(void);
	void getAccessory(void);
	void getActivePet(bool);
	void getActiveSkill(int);
	void getActiveSkill(void);
	void getActiveSkillShield(void);
	void getAliveTeamMembers(void);
	void getAttackAngle(void);
	void getBotSkill(void);
	void getBuffValue(int);
	void getBuffVisualStyle(int);
	int getCardValueForPassive(int, int);
	void getCarryableData(void);
	void getCarryableLastOwnerPlayerIndex(int);
	void getCharacterData(void);
	void getClosestBossTarget(int, int);
	void getClosestEnemy(int, int, bool, bool, LogicArrayList<int>*, bool, bool, bool);
	void getClosestFriendlyHealTargetForAI(void);
	void getClosestItemForAI(LogicArrayList<LogicData*>*, int);
	void getClosestProjectileFlyingAgainstYou(int);
	LogicProjectileServer* getControlledProjectile(void);
	void getCripplePercent(void);
	void getCurrentActiveOrCastingSkill(void);
	void getCurrentAttackSpeedTicks(void);
	LogicSkillData* getCurrentCastingSkill();
	int getDamageBuffTemporary();
	void getDamageEffect(void);
	void getDeathEffect(void);
	void getEnemyForAI(bool, bool, bool, LogicArrayList<LogicCharacterServer*>*);
	void getFurthesAwayOwnMinion(void);
	void getJumpZAtT(float, float, float, float, float);
	void getMaxChargedShots(void);
	int getMoveAngle();
	int getMovementSpeed(void);//
	void getNextSkill(void);
	void getNextSlipperyPosition(LogicVector2&);
	void getParentCharacter(void);
	int getPathLength();
	void getPosAtTick(int, LogicVector2&, LogicVector2&);
	int getPowerLevel(void);
	void getPrevX(void);
	void getPrevY(void);
	int getRadius(void);
	void getRandomTileOnVisionRange(LogicVector2*);
	void getRapidFireAttackPattern(void);
	void getRapidFireDamage(void);
	void getRapidFireProjectile(void);
	void getRapidFireRange(void);
	void getRapidFireSpread(void);
	void getReceivingDamagePercent(void);
	void getRegeneratePerSecond(void);
	int getReloadSpeedChangePercent(void);
	void getReloadTimeTicks(LogicSkillData*, int);
	void getShootPositionModifiers(int, int, int, int, int, int, int, LogicVector2&, LogicVector2&);
	int getSizeSubtilesForPathfinding(void);
	void getSkill(LogicSkillData*);
	void getSkill(String const&);
	void getSkill(int);
	void getSkillHoldedTicks(void);
	void getSlamZAtT(float);
	void getSpeedBuff(void);
	void getStarsForAI(void);
	void getState(void);
	void getType(void);
	LogicSkillData* getUltiSkill(void);
	void getVisionRange(void);
	LogicSkillData* getWeaponSkill(void);
	void getXForAutoshoot(void);
	void getYForAutoshoot(void);
	void giveCleanse(int);
	void giveCurse(int, int, int);
	void giveDamageAndSizeBuff(int, int);
	void giveDamageBuff(int, int);
	void giveDamageBuff2(int, int);
	void giveDamageBuffPermanent(int);
	void giveElectrocution(int, int, int, int, int, int, int, int);//
	void giveMaxHealthBuff(int, bool, bool, int);
	void giveReloadBuff(int, int);
	void giveReloadDebuff(int, int);
	void giveSilence(int);
	void giveSlipperyDebuff(int, int);
	void giveSpeedFasterBuff(int, int, bool);
	void giveSpeedFasterBuff2(int, int);
	void giveSpeedSlowerBuff(int, int);
	void gotDamageThisTick(int);
	void handleDelayedDeath(void);
	void handleDynamicWallClearing(void);
	void handleHealFromDamage(int, bool, LogicCharacterServer*, LogicData*);
	void handleMoveAndAttack(void);
	void handleTownCrushBossEnrage(int, int);
	void hasActiveAccessory(int, int);
	void hasActiveSkill(int);
	void hasBuff(int);
	bool hasCcImmunity(void);
	void hasChanneledSkillActive(void);
	void hasForcedMoveAngle(void);
	void hasSeen(LogicCharacterServer*);
	void hasSkill(int);
	void hasUlti(void);
	bool heal(int, int, bool, LogicData*);
	void holdSkillStarted(void);
	void increaseChargeUp(int);
	void increaseSize(int);
	void initializeMembers(void);
	void interruptAllSkills(bool);
	void isAlien(int);
	bool isAlive(void);
	void isBullChargeActive(void);
	void isChargeUpReady(void);
	void isForcedVisible(void);
	void isGiantGrowthed(void);
	void isGrappled(void);
	void isImmortalityActive(void);
	bool isImmuneAndBulletsGoThrough(void);
	void isImmuneToPushbackFromCharge(void);
	void isInAirFromPushback(void);
	void isInRange(int, LogicCharacterServer*, bool, bool, bool, bool);
	void isJumpingChargeActive(void);
	void isMinionSummoned(void);
	void isMoving(void);
	bool isObject(void);
	bool isPet(void);
	bool isPlayerControlRemoved(void);
	void isRadioactiveGlowActive(void);
	void isShieldActive(void);
	void isSprintActive(void);
	void isTargetVisibleToAttack(LogicCharacterServer*, bool);
	void isWhirlwinding(void);
	void kill(void);
	void markItemPickedUpTick(int);
	void meleeAttack(LogicCharacterServer*, int, int, int, int);
	void moveTo(int, int, bool, int, bool, bool);
	void overrideProjectiles(LogicProjectileData*, LogicProjectileData*, int);
	void pathFindToNextTarget(void);
	void pathfindTo(int, int, LogicVector2*, LogicPathFinder*, bool, bool, bool, bool);
	void pauseMovement(void);
	void pickedUpItemThisTick(int);
	void popTarget(void);
	void pushLaserBall(int, int, int, bool, int);
	void pushOutOfWalls(void);
	void rapidFireMeleeAttack(int, int, int, int, int);
	void recalculateBounceCharge(void);
	void removeCooldowns(void);
	void removeGameObjectReferences(LogicGameObjectServer*, int);
	void removeSelfAsChargeTarget(void);
	void resetAFKTicks(void);
	void resetEventsOnTick(void);
	void revealForBots(void);
	void scaleStatToLevel(int);
	void setCarryableAim(int, int);
	void setCarryableLink(LogicCharacterServer*);
	void setCharacterBuffingVariables(int, int, int, int);
	void setCharacterSummoningVariables(LogicCharacterData*, int, int, int, int);
	void setDefaultStartRotation(void);
	void setDraggingObject(LogicGameObjectServer*, int, int, bool);
	void setForcedAngle(int);
	void setGrappleTargetPos(int, int);
	void setImmunity(int, LogicData*, int);
	void setInvisible(int);
	void setItemSummoningVariables(LogicItemData*, int, int, int, int);
	void setMaxHealth(int);
	void setMinionDamageAndHealthBonuses(int, int);
	void setParentGID(int);
	void setPartialStunPromille(int);
	void setRadioactiveGlowSeconds(int);
	void setSelfDestructDamage(int);
	void setStartPosition(int, int, int);
	void setStartRotation(int);
	void setState(int, int);
	void setToxicFumesDamageIncrease(int);
	void setUpgrades(LogicHeroUpgrades*);
	void setVisionOverride(int, int, int);
	void shouldDestruct(void);
	void shouldSpawnPet(void);
	void showDamageNumber(int, int, LogicCharacterServer*);
	void skipPathPoints(int, int, int, LogicPathFinder*, bool);
	void spawnItem(LogicItemData*, int, int, int, int, int, int, int, int, LogicCharacterServer*, LogicBattleModeServer*, int);
	void stopGrapple(void);
	void stopMovement(void);
	static LogicCharacterServer* summonMinion(LogicCharacterData*, int, int, int, int, int, int, int, LogicBattleModeServer*, int, int, int, int, bool, bool, int, bool, int, bool, int, bool);//
	void suppressHealing(int, int);
	void swapSkillTo(int, LogicSkillData*);
	void switchRapidFireWeaponCounter(void);
	void throwCarryable(int, int, bool);
	void throwScrapAtOwnBase(void);
	void throwThis(bool);
	void tick(void);
	void tickAI(void);
	void tickAntiTeaming(void);
	void tickAutoUltiCharge(void);
	void tickBoss(void);
	void tickBossTownCrusher(void);
	void tickBot(void);
	void tickBotArtTest(void);
	void tickBotEmotes(void);
	void tickCarryable(void);
	void tickEffects(void);
	void tickEnrage(void);
	void tickGameModeLogic(void);
	void tickHeals(void);
	void tickInvisibility(void);
	void tickMovePet(void);
	void tickNpcSkills(void);
	void tickRapidFire(void);
	void tickSelfDestruct(void);
	void tickSkills(void);
	void tickSpawnMinions(void);
	void tickStarPowers(void);
	void tickTile(void);
	void tickTimers(void);
	void tickTrain(void);
	void tickWhirlwind(void);
	void transformPushBackLengthToStrength(int);
	void transformPushBackStrengthToLength(int);
	void triggerAreaEffect(LogicAreaEffectData*, int, int, int, int);
	void triggerBlink(int, int, LogicAreaEffectData*, LogicAreaEffectData*, int, int);
	void triggerCharacterBuffingProjectile(LogicProjectileData*, int, int, int, int, int, int);
	void triggerCharacterTransformingProjectile(LogicProjectileData*, LogicCharacterData*, int, int, int, int, int, int, int, int);
	void triggerCharge(int, int, int, int, int, int, bool, int, LogicAreaEffectData*, LogicItemData*, int, int, int, bool, LogicArrayList<LogicVector2*>*, LogicAreaEffectData*);
	void triggerChargeEndAreaEffect(void);
	void triggerGiantGrowth(int);
	void triggerGrapple(int, int, int);
	void triggerLowerCooldowns(int);
	void triggerPushback(int, int, int, bool, bool, bool, bool, bool, bool, bool, bool, bool, int);
	void triggerRaiseDead(void);
	void triggerRapidFire(int, int, int, int, int, int, int, int, int, int, LogicProjectileData*, bool, bool, int, bool);
	void triggerResurrect(void);
	void triggerShake(void);
	void triggerStun(int, bool);//
	void triggerWhirlwind(int, int, int);
	void turnAngleTowards(float, int, float);
	void ultiDisabled(void);
	void ultiEnabled(void);
	void ultiUsed(void);
	void updateChargeDamage(void);
	void updateMoveDirection(LogicVector2*, LogicVector2*, int, int);
	void updateSpellCastingDirection(int, int);
	void wasVisibleByActionWithin(int);
};
#endif