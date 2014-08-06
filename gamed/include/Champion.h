#ifndef _CHAMPION_H
#define _CHAMPION_H

#include "Inventory.h"
#include "Unit.h"
#include "Spell.h"
#include <vector>






class Champion : public Unit {

protected:
   std::string type;
   std::vector<Spell*> spells;
   uint8 skillPoints;
   uint8 level;
   float xp;

   
public:

   Champion(const std::string& type, Map* map, uint32 id);
   const std::string& getType() { return type; }
   
   Spell* castSpell(uint8 slot, float x, float y, Unit* target);
   Spell* levelUpSpell(uint8 slot);
   
   virtual void update(int64 diff);
   
   Inventory inventory;

   void setSkillPoints(int _skillPoints){
       skillPoints = (uint8)_skillPoints;
   }
   
   uint8 getSkillPoints() const { return skillPoints; }
   
   void teleportTo(float _x, float _y){
   needsToTeleport = true;
   teleportToX = (_x-MAP_WIDTH) / 2; 
   teleportToY = (_y-MAP_HEIGHT)/2;
   setPosition(_x, _y);
   }

};

#endif