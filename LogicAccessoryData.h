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
	bool getInterruptsAction()
	{
		return ((bool (*)(LogicAccessoryData*))base + 0x82AA14)(this);
	}
	bool getStopMovement()
	{
		return ((bool (*)(LogicAccessoryData*))base + 0x82A994)(this);
	}
	int getActivationDelay()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82A964)(this);
	}
	int getActiveTicks()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82A974)(this);
	}
	int getCoolDown()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82A914)(this);
	}
	int getCustomValue1()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82AB24)(this);
	}
	int getCustomValue2()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82AB34)(this);
	}
	int getCustomValue3()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82AB44)(this);
	}
	int getCustomValue4()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82AB54)(this);
	}
	int getCustomValue5()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82AB64)(this);
	}
	int getCustomValue6()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82AB74)(this);
	}
	void* getCustomObject()
	{
		return ((void* (*)(LogicAccessoryData*))base + 0x82AB14)(this);
	}
	bool getShowCountdown()
	{
		return ((bool (*)(LogicAccessoryData*))base + 0x82A984)(this);
	}
};
#endif