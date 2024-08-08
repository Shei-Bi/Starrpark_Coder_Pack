#ifndef LOGICHEROENTRY_H
#define LOGICHEROENTRY_H
#include "LogicArrayList.h"
#include "LogicCharacterData.h"
#include "LogicHeroUpgrades.h"
#include "LogicBattleEmotes.h"
#include "LogicBattleSprays.h"
#include "LogicSkinData.h"

class LogicHeroEntry
{
public://found names from json encode lol
   LogicCharacterData* hero;
   LogicHeroUpgrades* upgrades;
   LogicBattleEmotes* Emotes;
   LogicBattleSprays* Sprays;
   LogicSkinData* Skin;
   LogicSkinData* unk1;
   int unk2;
};
#endif