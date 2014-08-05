#include "Spell.h"
#include "LuaScript.h"
#include "sol/state.hpp"
#include "Game.h"
#include "Map.h"
#include "Vector2.h"

/**
 * Called when the character casts the spell
 */
bool Spell::cast(float x, float y, Unit* u) {
   state = STATE_CASTING;
   currentCastTime = castTime;
   
   this->x = x;
   this->y = y;
   this->target = u;
   
   return true;
}

/**
 * Called when the spell is finished casting and we're supposed to do things
 * such as projectile spawning, etc.
 */
void Spell::finishCasting() {
    
   doLua();
   
   state = STATE_COOLDOWN;
   currentCooldown = getCooldown();
}

std::string Spell::getStringForSlot(){
    
    switch(getSlot()){
        case 0:
            return "Q";
        case 1:
            return "W";
        case 2:
            return "E";
        case 3:
            return "R";
    }
    
    return "undefined";
    
}

void Spell::doLua(){
    
    printf("Spell from slot %i", getSlot());

    LuaScript script;
  
   
   float ownerX = owner->getX();
   float ownerY = owner->getY();
   
   float spellX = x;
  
   float spellY = y;
   
   script.lua.set_function("getOwnerX", [&ownerX]() { return ownerX; });
   
   script.lua.set_function("getOwnerY", [&ownerY]() { return ownerY; });
   
   script.lua.set_function("getSpellToX", [&spellX]() { return spellX; });
      
   script.lua.set_function("getSpellToY", [&spellY]() { return spellY; });
   
   std::string scriptloc = "../../lua/champions/" + owner->getType() + "/" + getStringForSlot() + ".lua"; //lua/championname/(q/w/e/r), example: /lua/Ezreal/q, also for stuff like nidalee cougar they will have diff folders!

   printf("Spell script loc is: %s \n" , scriptloc.c_str());
   script.loadScript(scriptloc); //todo: abstract class that loads a lua file for any lua
   
}

/**
 * Called every diff milliseconds to update the spell
 */
void Spell::update(int64 diff) {
   switch(state) {
      case STATE_READY:
         return;
      case STATE_CASTING:
         currentCastTime -= diff/1000000.f;
         if(currentCastTime < 0) {
            finishCasting();
         }
         break;
      case STATE_COOLDOWN:
         currentCooldown -= diff/1000000.f;
         if(currentCooldown < 0) {
            state = STATE_READY;
         }
         break;
   }
}