#include "Champions/Ezreal/ArcaneShift.h"
#include "Game.h"
#include "Map.h"
#include "Vector2.h"
#include "LuaScript.h"
#include "sol/state.hpp"

void ArcaneShift::finishCasting() {
   Spell::finishCasting();

   LuaScript script;
  
   
   float ownerX = owner->getX();
   
   script.lua.set_function("getOwnerX", [&ownerX]() { return ownerX; });

   script.loadScript("../../lua/ArcaneShift.lua"); //todo: abstract class that loads a lua file for any lua
   
   
   printf("Teleporting to X:%f , Y:%f", x, y);

   Vector2 trueCoords;
   
   Vector2 cur(owner->getX(), owner->getY());
   
   Vector2 to(x, y);
   
   Vector2 sub = to - cur;
   
   if(sub.Length() > 475){ 
   
   sub = sub.Normalize(); 
   
   trueCoords = cur + (sub * 475); 
   }else{ 
       trueCoords = Vector2(x, y);
   }

   owner->needsToTeleport = true;
   owner->teleportToX = (trueCoords.X-MAP_WIDTH) / 2; 
   owner->teleportToY = (trueCoords.Y-MAP_HEIGHT)/2;
   
   
   owner->setPosition(trueCoords.X, trueCoords.Y);
   
   
}

void ArcaneShift::applyEffects(Target* t, Projectile* p) {
    
    
}