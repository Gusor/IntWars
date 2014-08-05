#ifndef _CHAMPION_EZREAL_H
#define _CHAMPION_EZREAL_H

#include "Champion.h"
#include "MysticShot.h"
#include "ArcaneShift.h"

class Ezreal : public Champion {

public:
   Ezreal(Map* map, uint32 id) : Champion("Ezreal", map, id) {
      spells.push_back(new MysticShot(this));
      spells.push_back(new MysticShot(this));
      spells.push_back(new ArcaneShift(this));
      spells.push_back(new MysticShot(this));
      
      stats->setCurrentHealth(430.0f);
      stats->setMaxHealth(430.0f);
      stats->setCurrentMana(280.0f);
      stats->setMaxMana(280.0f);
      stats->setBaseAd(50.2f);
      stats->setRange(550.f);
      stats->setMovementSpeed(325.f);
      stats->setArmor(19.5f);
      stats->setMagicArmor(30.f);
      stats->setHp5(5.5f);
      stats->setMp5(7.0f);
      stats->setGoldPer5(9.5f);
   }


};

#endif