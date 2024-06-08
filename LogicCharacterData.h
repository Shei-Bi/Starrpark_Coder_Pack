#ifndef LOGICCHARACTERDATA_H
#define LOGICCHARACTERDATA_H
#include "Hook.h"
#include"LogicData.h"
class LogicCharacterData : public LogicData
{
public:
	int getUniqueProperty()
	{
		return ((int (*)(LogicCharacterData*))base + 0x83A234)(this);
	}
	int getUniquePropertyValue1()
	{
		return ((int (*)(LogicCharacterData*))base + 0x83A244)(this);
	}
};
#endif