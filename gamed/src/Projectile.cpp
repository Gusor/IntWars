#include <map>

#include "Map.h"
#include "Projectile.h"
#include "Spell.h"
#include "Unit.h"

void Projectile::update(int64 diff) {

   if(!target) {
      setToRemove();
      return;
   }
   
   if(target->isSimpleTarget()) { // Skillshot
      const std::map<uint32, Object*>& objects = map->getObjects();
      for(auto& it : objects) {
         if(isToRemove()) {
            return;
         }
         
         if(collide(it.second)) {
            printf("Collide with 0x%08X !\n", it.second->getNetId());
            originSpell->applyEffects(it.second, this);
         }
      }
   } else {
      Unit* u = static_cast<Unit*>(target);
      if(collide(u)) { // Autoguided spell
         if(originSpell) {
            originSpell->applyEffects(u, this);
         } else { // auto attack
            owner->autoAttackHit(u);
            setToRemove();
         }
      }
   }
   
   Object::update(diff);
   
}