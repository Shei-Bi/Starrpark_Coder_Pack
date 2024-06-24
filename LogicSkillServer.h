#ifndef LSS_H
#define LSS_H
#include "LogicMath.h"
#include "LogicSkillData.h"
#include "LogicCharacterServer.h"
#include "BitStream.h"

class LogicSkillServer
{
public:
	LogicSkillData* SkillData;//0
	int ActiveTime;//8
	int MaxActiveTime;//12
	int CoolDown;//16
	int field_14;//20
	int Charges;//24
	int field_1C;//28
	int X;//32
	int Y;//36
	bool OnActivate;//40
	bool Boolean2;//41
	char gap1[6];
	int Level;//48
	int ChargesPerShoot;//52
	bool IsUltiSkill;//53
	LogicSkillServer(LogicSkillData*, int);

	void addCharge(LogicCharacterServer*, int);
	void encode(BitStream* stream, bool isOwn, LogicCharacterServer* owner) {
		stream->writePositiveVIntMax255OftenZero(ActiveTime / 50);
		stream->writePositiveVIntMax255OftenZero(MaxActiveTime / 50);
		stream->writeBoolean(OnActivate);
		stream->writeBoolean(Boolean2);
		stream->writePositiveVIntMax255OftenZero(CoolDown / 50);
		if (SkillData->getMaxCharge() >= 1) {
			if (SkillData->HoldToShoot) stream->writePositiveIntMax4095(Charges / 20);
			else stream->writePositiveIntMax4095(Charges);
		}
	}
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