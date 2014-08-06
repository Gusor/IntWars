/*#include "Champions/Ezreal/MysticShot.h"

#include "Game.h"
#include "Map.h"

#include "Vector2.h"

#define MYSTICSHOT_RANGE 1150

/**
 * Called when the character casts the spell
 */
/*bool MysticShot::cast(float x, float y, Unit* u) {
   
   owner->setTarget(0); // stop movement
   return Spell::cast(x, y, u);
}*/

/**
 * This is called when the spell is finished casting, and we're supposed to
 * create the projectile
 */
/*void MysticShot::finishCasting() {
   Spell::finishCasting();

  
  /* Map* m = owner->getMap();
   
   Vector2 trueCoords;
   Vector2 cur(owner->getX(), owner->getY());
   Vector2 to(x, y);
   
   Vector2 sub = to - cur;

   sub = sub.Normalize(); 
   trueCoords = cur + (sub * MYSTICSHOT_RANGE);
   
   Projectile* p = new Projectile(owner->getMap(), GetNewNetID(), owner->getX(), owner->getY(), 30, owner, new Target(trueCoords.X, trueCoords.Y), this, 2000.f);
   owner->getMap()->addObject(p);
}*/

/**
 * This will be called when Mystic's Shot projectile hits a unit
 */
/*void MysticShot::applyEffects(Target* t, Projectile* p) {
   if(!p) {
      return;
   }
   
   Unit* u = dynamic_cast<Unit*>(t);
   if(!u) {
      return;
   }
   
   if(u->getSide() == owner->getSide()) {
      return;
   }
   
   owner->dealDamageTo(u, damage[level-1], DAMAGE_TYPE_PHYSICAL, DAMAGE_SOURCE_SPELL);
   
   p->setToRemove();
}*/