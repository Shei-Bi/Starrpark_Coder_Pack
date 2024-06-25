#ifndef LOGICCHARACTERDATA_H
#define LOGICCHARACTERDATA_H
#include "Hook.h"
#include"LogicData.h"
class LogicCharacterData : public LogicData
{
public:
	char gap1[492];
	int Type;
	int getUniqueProperty()
	{
		return ((int (*)(LogicCharacterData*))(base + 0x83A234))(this);
	}
	int getUniquePropertyValue1()
	{
		return ((int (*)(LogicCharacterData*))(base + 0x83A244))(this);
	}
	bool isHero() {
		return Type == 0;
	}
	int getSpeed()
	{
		return ((int (*)(LogicCharacterData*))(base + 0x839428))(this);
	}
};
#endif