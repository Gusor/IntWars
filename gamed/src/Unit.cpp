#include "Unit.h"
#include "AI.h"
#include "Map.h"
#include "Game.h"

#include <algorithm>

using namespace std;

Unit::~Unit() {
   delete stats;
   if(ai) {
      delete ai;
   }
}

void Unit::update(int64 diff) {
   if(unitTarget && distanceWith(unitTarget) <= stats->getRange()) {
      if(autoAttackCooldown <= 0) {
         map->getGame()->notifyAutoAttack(this, unitTarget);
         Projectile* p = new Projectile(map, GetNewNetID(), x, y, 10, this, unitTarget, 0, getAttackProjectileSpeed());
         map->addObject(p);
         autoAttackCooldown = 1.f/(stats->getTotalAttackSpeed());
      }
   }
   else {
      Object::update(diff);
   }
   
   if(autoAttackCooldown > 0) {
      autoAttackCooldown -= diff/1000000.f;
   }
   
   if(ai) {
      ai->update(diff);
   }
   
   statUpdateTimer += diff;
   if(statUpdateTimer >= 1000000) { // update stats (hpregen, manaregen) every seconds
      stats->update(statUpdateTimer);
      statUpdateTimer = 0;
   }
}

void Unit::autoAttackHit(Unit* target) {
   dealDamageTo(target, stats->getTotalAd(), DAMAGE_TYPE_PHYSICAL, DAMAGE_SOURCE_ATTACK);
}

/**
 * TODO : handle armor, magic resistance [...]
 */
void Unit::dealDamageTo(Unit* target, float damage, DamageType type, DamageSource source) {
   printf("0x%08X deals %f damage to 0x%08X !\n", getNetId(), damage, target->getNetId());
   target->getStats().setCurrentHealth(max(0.f, target->getStats().getCurrentHealth()-damage));
   map->getGame()->notifyDamageDone(this, target, damage);
}