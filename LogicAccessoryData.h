#ifndef LAD_H
#define LAD_H
#include "Hook.h"
#include"LogicData.h"
class LogicAccessoryData : public LogicData
{
public:
	int getMaxCharge()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x873D40)(this);
	}
};
#endif