#ifndef LOGICACCESSORY_H
#define LOGICACCESSORY_H
#include "LogicMath.h"
#include "LogicSkillData.h"
#include "LogicCharacterServer.h"
#include "LogicAccessoryData.h"
#include "BitStream.h"
#include "LogicDataTables.h"
#include "LogicProjectileData.h"
#include "LogicProjectileServer.h"

class LogicAccessory
{
public:
	LogicAccessoryData* AccessoryData;
	int Uses;
	int UNK2;
	int CoolDown;
	int State;
	int Type;
	int ActivationDelay;
	int X;
	int Y;
	int TicksActive;
	bool IsActive;
	int qword30;
	int field_34;
	int StartUsingTick;
	int Angle;

	LogicAccessory(LogicAccessoryData*, int);
	void encode(BitStream*, bool);
	void triggerAccessory(LogicCharacterServer*, int, int);
	void activateAccessory(LogicCharacterServer*);
	int checkCurrentAccessoryAvailability(LogicCharacterServer*);
	void interrupt(bool, LogicCharacterServer*);
	void updateAccessory(LogicCharacterServer*);
	void tickAccessory(LogicCharacterServer*);
	void endAccessoryActivation();
};
LogicAccessory::LogicAccessory(LogicAccessoryData* data, int count) {
	AccessoryData = data;
	IsActive = false;
}
void LogicAccessory::encode(BitStream* stream, bool isSelf) {
	if (isSelf) {
		stream->writePositiveVIntMax255OftenZero(CoolDown);
		stream->writePositiveVIntMax255OftenZero(State);
	}
	else stream->writeBoolean(State == 1);
	if (State == 1) {
		stream->writePositiveIntMax16383(StartUsingTick);
		stream->writePositiveIntMax511(Angle);
	}
}
int LogicAccessory::checkCurrentAccessoryAvailability(LogicCharacterServer* Owner) {
	if (IsActive) return 1;
	if (Uses < 1) return 4;
	if (CoolDown > 0) return 5;
	return 0;
}
void LogicAccessory::triggerAccessory(LogicCharacterServer* owner, int x, int y) {
	State = checkCurrentAccessoryAvailability(owner);
	if (State != 0) return;
	if (!owner) return;
	if (CoolDown > 0) return;
	if (owner->getCurrentCastingSkill() && owner->getCurrentCastingSkill()->BehaviorType == 2) return;
	if (AccessoryData->getInterruptsAction()) owner->interruptAllSkills(true);
	if (AccessoryData->getStopMovement()) owner->stopMovement();
	IsActive = true;
	X = x;
	Y = y;
	StartUsingTick = owner->getLogicBattleModeServer()->getTick();
	if (AccessoryData->getActivationDelay() <= 0) {
		activateAccessory(owner);
	}
	Uses--;
}
void LogicAccessory::activateAccessory(LogicCharacterServer* owner) {
	if (AccessoryData->getActiveTicks() < 1) {
		/*
		Refactor. Reason: same code
		--Shei
		*/
		endAccessoryActivation();
	}
	else {
		TicksActive = 0;
		tickAccessory(owner);
		TicksActive++;
	}
}
void LogicAccessory::updateAccessory(LogicCharacterServer* owner) {
	State = checkCurrentAccessoryAvailability(owner);
	CoolDown = LogicMath::max(0, CoolDown - 1);
	if (IsActive) {
		if (ActivationDelay < 1) {
			if (TicksActive >= AccessoryData->getActiveTicks()) {
				IsActive = 0;
				CoolDown = AccessoryData->getCoolDown();
			}
			else {
				tickAccessory(owner);
				TicksActive++;
			}
		}
		else {
			ActivationDelay--;
			if (ActivationDelay < 1) activateAccessory(owner);
		}
	}
}
void LogicAccessory::tickAccessory(LogicCharacterServer* owner) {
	switch (Type) {
	case 3://spin_shoot
		owner->setForcedAngle(LogicMath::normalizeAngle360(owner->getMoveAngle() + 90));
		if (TicksActive % AccessoryData->getCustomValue1() == 0) {
			LogicProjectileData* projectileData = LogicDataTables::getProjectileByName(AccessoryData->getCustomObject(), nullptr);
			if (projectileData) {
				StartUsingTick = owner->getLogicBattleModeServer()->getTick();
				int range = AccessoryData->getCustomValue4() + AccessoryData->getCustomValue5() * (TicksActive / AccessoryData->getCustomValue1());
				int angle = TicksActive / AccessoryData->getCustomValue1() * AccessoryData->getCustomValue2();
				int deltaX = LogicMath::getRotatedX(range, 0, angle) * 1;
				int deltaY = LogicMath::getRotatedY(range, 0, angle) * 1;
				LogicTileMap* tileMap = owner->getLogicBattleModeServer()->getTileMap();
				LogicProjectileServer::shootProjectile(
					300 * deltaX / range + owner->GetX(),//bullet spawn 300 offset from character
					300 * deltaY / range + owner->GetY(),//其实就是在离角色一格远的地方发射子弹防止子弹把角色脸挡住
					owner,
					owner,
					projectileData,
					LogicMath::clamp(deltaX + owner->GetX(), 1, tileMap->LogicWidth - 2),
					LogicMath::clamp(deltaY + owner->GetY(), 1, tileMap->LogicHeight - 2),
					AccessoryData->getCustomValue3(),
					AccessoryData->getCustomValue6(),
					0,
					false,
					0,
					owner->getLogicBattleModeServer(),
					0,
					4//1 普攻 2 大招 3星辉 4 妙具 
				);
			}
		}
		break;

	}
}
void LogicAccessory::endAccessoryActivation()
{
	if (IsActive)
	{
		IsActive = 0;
		CoolDown = AccessoryData->getCoolDown();
	}
}
void LogicAccessory::interrupt(bool a2, LogicCharacterServer* a3)
{
	;
}
#endif