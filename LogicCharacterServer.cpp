#include "LogicCharacterServer.h"
#include "LogicArrayList.h"
#include "LogicSkillData.h"
#include "LogicSkillServer.h"
#include "LogicAccessory.h"
#include "LogicProjectileServer.h"
void LogicCharacterServer::addConsumableShield(int amount)
{
	ConsumableShield = amount;
	ConsumableShieldMax = amount;
}
void LogicCharacterServer::tick()
{
	addConsumableShield(114514);
}
int LogicCharacterServer::getCardValueForPassive(int type, int index) {
	return -1;
}
LogicSkillData* LogicCharacterServer::getCurrentCastingSkill() {
	if (Skills.length < 1) return nullptr;
	for (int i = 0;i < Skills.length;i++) {
		LogicSkillServer* skill = Skills[i];
		if (skill->ActiveTime >= 1 || skill->OnActivate && skill->SkillData->getCastingTime() > 0) return skill->SkillData;
	}
	return nullptr;
}
void LogicCharacterServer::interruptAllSkills(bool ignoreAccessory) {
	return ((void (*)(LogicCharacterServer*, bool))base + 0x88DFEC)(this, ignoreAccessory);
}
void LogicCharacterServer::stopMovement() {
	MoveStartTick = getLogicBattleModeServer()->getTicksGone() - 1;
	MoveEndTick = MoveStartTick;
}