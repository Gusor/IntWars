#include "Champion.h"
#include "RAFManager.h"
#include "Inibin.h"

Champion::Champion(const std::string& type, Map* map, uint32 id) : Unit(map, id, new Stats()), type(type), skillPoints(1), level(1)  {
   stats->setGold(475.0f);
   stats->setAttackSpeedMultiplier(1.0f);

   std::vector<unsigned char> iniFile;
   if(!RAFManager::getInstance()->readFile("DATA/Characters/"+type+"/"+type+".inibin", iniFile)) {
      printf("ERR : couldn't find champion stats for %s\n", type.c_str());
      return;
   }
   
   
   
   Inibin inibin(iniFile);

   printf("Loading champion type %s", type.c_str());
   
   
   stats->setCurrentHealth(inibin.getFloatValue("Data", "BaseHP")); // Why rito ? why maxHP as a string and mana as a float ?
   stats->setMaxHealth(inibin.getFloatValue("Data", "BaseHP"));
   stats->setCurrentMana(inibin.getFloatValue("Data", "BaseMP"));
   stats->setMaxMana(inibin.getFloatValue("Data", "BaseMP"));
   stats->setBaseAd(inibin.getFloatValue("DATA", "BaseDamage"));
   stats->setRange(inibin.getFloatValue("DATA", "AttackRange"));
   stats->setMovementSpeed(inibin.getFloatValue("DATA", "MoveSpeed"));
   stats->setArmor(inibin.getFloatValue("DATA", "Armor"));
   stats->setMagicArmor(inibin.getFloatValue("DATA", "SpellBlock"));
   stats->setHp5(inibin.getFloatValue("DATA", "BaseStaticHPRegen"));
   stats->setMp5(inibin.getFloatValue("DATA", "BaseStaticMPRegen"));
   
   
   
   spells.push_back(new Spell(this, inibin.getStringValue("Data", "Spell1"), 0));
   spells.push_back(new Spell(this, inibin.getStringValue("Data", "Spell2"), 1));
   spells.push_back(new Spell(this, inibin.getStringValue("Data", "Spell3"), 2));
   spells.push_back(new Spell(this, inibin.getStringValue("Data", "Spell4"), 3));
}

Spell* Champion::castSpell(uint8 slot, float x, float y, Unit* target) {
   if(slot >= spells.size()) {
      return 0;
   }
   
   Spell* s = spells[slot];
   
   s->setSlot(slot);//temporary hack until we redo spells to be almost fully lua-based
   
   if(s->getCost() > stats->getCurrentMana() || s->getState() != STATE_READY) {
      return 0;
   }
   
   s->cast(x, y, target);
   stats->setCurrentMana(stats->getCurrentMana()-s->getCost());
   return s;
}

Spell* Champion::levelUpSpell(uint8 slot) {
   if(slot >= spells.size()) {
      return 0;
   }
   
   if(skillPoints == 0) {
      return 0;
   }
   
   spells[slot]->levelUp();
   --skillPoints;
   
   return spells[slot];
}

void Champion::update(int64 diff) {
   Unit::update(diff);
   
   for(Spell* s : spells) {
      s->update(diff);
   }
}

uint32 Champion::getChampionHash() {
   char szSkin[4];
   sprintf(szSkin, "%02d", skin);
   uint32 hash = 0;
   const char *gobj = "[Character]";
   for(unsigned int i = 0; i < strlen(gobj); i++) {
     hash = tolower(gobj[i]) + (0x1003F * hash);
   }
   for(unsigned int i = 0; i < type.length(); i++) {
     hash = tolower(type[i]) + (0x1003F * hash);
   }
   for(unsigned int i = 0; i < strlen(szSkin); i++) {
     hash = tolower(szSkin[i]) + (0x1003F * hash);
   }
   return hash;
}