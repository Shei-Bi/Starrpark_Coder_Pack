#ifndef LSS_H
#define LSS_H
#include "LogicMath.h"
#include "LogicSkillData.h"
#include "LogicCharacterServer.h"
class LogicSkillServer
{
public:
	LogicSkillData* SkillData;
	int ActiveTime;
	int MaxActiveTime;
	int CoolDown;
	int field_14;
	int Charges;
	int field_1C;
	int X;
	int Y;
	bool OnActivate;
	bool Boolean2;
	char gap1[6];
	int Level;
	int ChargesPerShoot;
	bool IsUltiSkill;
	LogicSkillServer(LogicSkillData*, int);

	void addCharge(LogicCharacterServer*, int);
private:

};
LogicSkillServer::LogicSkillServer(LogicSkillData* data, int isUltiSkill) {
	SkillData = data;
	Level = 0;
	ChargesPerShoot = 1;
	Charges = LogicMath::max(1000, 1000 * data->getMaxCharge());
	IsUltiSkill = isUltiSkill;
}
void LogicSkillServer::addCharge(LogicCharacterServer* owner, int charges) {
	Charges += 10 * charges * ChargesPerShoot;
	int maxCharge = 1000 * (SkillData->getMaxCharge() + LogicMath::positify(owner->getCardValueForPassive(48, 1)));
	if (Charges > maxCharge) Charges = maxCharge;
}
#endif