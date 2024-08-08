#ifndef LOGICSKINDATA_H
#define LOGICSKINDATA_H
#include "Hook.h"
#include"LogicData.h"

class LogicSkinData : public LogicData
{
public:
	LogicSkinData* getPetSkin() {
		return *(LogicSkinData**)((char*)this + 176);
	}
};
#endif