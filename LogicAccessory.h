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
	LogicAccessoryData* AccessoryData;//0
	int Uses;//8
	int UNK2;//12
	int CoolDown;//16
	int State;//20
	int Type;//24
	int ActivationDelay;//28
	int X;//32
	int Y;//36
	int TicksActive;//40
	bool IsActive;//44
	int qword30;//48
	int field_34;//52
	int StartUsingTick;//56
	int Angle;//60
	char gap32878[4];
	bool IsWeaponChangeEnabled;//68
	bool IsUltiChangeEnabled;//69
	bool HasActivated;

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
	if (IsActive && !HasActivated) return 1;
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
	else {
		ActivationDelay = AccessoryData->getActivationDelay();
		//todo: StopPetForDelay
	}
	owner->blockHealthRegen();
	Uses--;
}
void LogicAccessory::activateAccessory(LogicCharacterServer* owner) {
	switch (Type) {
	case 8://heal
		if (AccessoryData->getSubType() == 1) {
			int amount = AccessoryData->getCustomValue1() * owner->HitpointsMax / 100;
			if (amount == 0) amount = owner->HitpointsMax - owner->Hitpoints;//睡眠仪
			owner->heal(owner->Index, amount, true, nullptr);
		}
		else if (AccessoryData->getSubType() == 2) {
			owner->addExtraHealthRegen(AccessoryData->getCustomValue1() * owner->HitpointsMax / 100, AccessoryData->getActiveTicks(), owner->Index, AccessoryData);
		}
		break;
	case 31://ulti_change
		switch (AccessoryData->getSubType())
		{
		case 1://buzz
			owner->chargeUlti(AccessoryData->getCustomValue5(), false, true, owner->getPlayer(), owner);
			break;
		}
		break;
	}
	if (AccessoryData->getActiveTicks() < 1) {
		if (Type == 31) {
			HasActivated = true;
		}
		else {
			IsActive = false;
		}
		CoolDown = AccessoryData->getCoolDown();
	}
	else {
		TicksActive = 0;
		tickAccessory(owner);
		TicksActive++;
	}
}
void LogicAccessory::updateAccessory(LogicCharacterServer* owner) {
	IsWeaponChangeEnabled = true;
	IsUltiChangeEnabled = true;
	State = checkCurrentAccessoryAvailability(owner);
	CoolDown = LogicMath::max(0, CoolDown - 1);
	if (IsActive && !HasActivated) {
		if (ActivationDelay < 1) {
			if (TicksActive >= AccessoryData->getActiveTicks()) {
				if (Type == 31) {
					HasActivated = true;
				}
				else {
					IsActive = false;
				}
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
	owner->getPlayer()->AccessoryUses = Uses;
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
					300 * deltaX / range + owner->getX(),//bullet spawn 300 offset from character
					300 * deltaY / range + owner->getY(),//��ʵ���������ɫһ��Զ�ĵط������ӵ���ֹ�ӵ��ѽ�ɫ����ס
					owner,
					owner,
					projectileData,
					LogicMath::clamp(deltaX + owner->getX(), 1, tileMap->LogicWidth - 2),
					LogicMath::clamp(deltaY + owner->getY(), 1, tileMap->LogicHeight - 2),
					AccessoryData->getCustomValue3(),
					AccessoryData->getCustomValue6(),
					0,
					false,
					0,
					owner->getLogicBattleModeServer(),
					0,
					4//1 �չ� 2 ���� 3�ǻ� 4 ��� 
				);
			}
		}
	}
}
void LogicAccessory::endAccessoryActivation()
{
	if (IsActive)
	{
		IsActive = false;
		CoolDown = AccessoryData->getCoolDown();
		HasActivated = false;
	}
}
void LogicAccessory::interrupt(bool ignoreAccessory, LogicCharacterServer* owner)
{
	if (ignoreAccessory) return;
	if ((Type == 23 || Type == 31) && owner->Hitpoints > 0) return;
	endAccessoryActivation();
}
#endif