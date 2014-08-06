#include "Spell.h"
#include "Map.h"
#include "Game.h"
#include "RAFManager.h"
#include "Champion.h"
#include "Inibin.h"
#include "LuaScript.h"

using namespace std;

Spell::Spell(Champion* owner, const std::string& spellName, uint8 slot) : owner(owner), spellName(spellName), level(0), slot(slot), state(STATE_READY), currentCooldown(0), currentCastTime(0) {
   std::vector<unsigned char> iniFile;
   if(!RAFManager::getInstance()->readFile("DATA/Spells/"+spellName+".inibin", iniFile)) {
      if(!RAFManager::getInstance()->readFile("DATA/Characters/"+owner->getType()+"/"+spellName+".inibin", iniFile)) {
         printf("ERR : couldn't find spell stats for %s\n", spellName.c_str());
         return;
      }
   }
   
   Inibin inibin(iniFile);
   
   for(int i = 0; i < 5; ++i) {
      char c = '0'+i+1;
      cooldown[i] = inibin.getFloatValue("SpellData", string("Cooldown")+c);
   }
   
   castTime = ((1.f+inibin.getFloatValue("SpellData", "DelayCastOffsetPercent")))/2.f;

   printf("CastTime is %f for spell : %s", castTime, spellName.c_str() );
}


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
   
   
   script.lua.set_function("teleportTo", [this](float _x, float _y) { // expose teleport to lua
   owner->needsToTeleport = true;
   owner->teleportToX = (_x-MAP_WIDTH) / 2; 
   owner->teleportToY = (_y-MAP_HEIGHT)/2;
   owner->setPosition(_x, _y);
   return;
   });
   
   
   script.lua.set_function("addProjectile", [this](float toX, float toY, float projectileSpeed) { 
   owner->setPosition(owner->getX(), owner->getY()); // stop moving
   Projectile* p = new Projectile(owner->getMap(), GetNewNetID(), owner->getX(), owner->getY(), 30, owner, new Target(toX, toY), this, projectileSpeed);
   owner->getMap()->addObject(p);
   owner->getMap()->getGame()->notifyProjectileSpawn(p);

   return;
   });
   
   


   
   std::string scriptloc = "../../lua/champions/" + owner->getType() + "/" + getStringForSlot() + ".lua"; //lua/championname/(q/w/e/r), example: /lua/Ezreal/q, also for stuff like nidalee cougar they will have diff folders!

   printf("Spell script loc is: %s \n" , scriptloc.c_str());
   script.lua.script("package.path = '../../lua/lib/?.lua;' .. package.path"); //automatically load vector lib so scripters dont have to worry about path

   try{
   script.loadScript(scriptloc); //todo: abstract class that loads a lua file for any lua
   script.lua.script("finishCasting()");
   }catch(sol::error e){//lua error? don't crash the whole server
       printf("%s", e.what());
   }
}

/**
 * Called every diff milliseconds to update the spell
 */
void Spell::update(int64 diff) {
   switch(state) {
      case STATE_READY:
         return;
      case STATE_CASTING:
          
    printf("Update spell %s , currentCastTime %f\n" , getStringForSlot().c_str(), (float)currentCastTime);
         currentCastTime -= diff/1000000.f;
         if(currentCastTime <= 0) {
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

uint32 Spell::getId() const {
   return RAFFile::getHash(spellName);
}

void Spell::applyEffects(Target* t, Projectile* p) {
   
}