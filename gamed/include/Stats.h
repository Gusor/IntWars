#ifndef __H_STATS
#define __H_STATS

#include <map>
#include <algorithm>

#include "stdafx.h"
#include "common.h"

enum FieldMaskOne : uint32
{
   FM1_Gold        = 0x00000001,
   FM1_Gold_2      = 0x00000002,
   FM1_SPELL       = 0x00000004 // Sending short 0x108[1248] activates spells 1/2/3/4
};

enum FieldMaskTwo : uint32
{
   FM2_Base_Ad         = 0x00000020, // champ's base ad that increase every level. No item bonus should be added here
   FM2_Base_Ap         = 0x00000040,
   FM2_Crit_Chance     = 0x00000100, // 0.5 = 50%
   FM2_Armor           = 0x00000200,
   FM2_Magic_Armor     = 0x00000400,
   FM2_Hp5             = 0x00000800,
   FM2_Mp5             = 0x00001000,
   FM2_Range           = 0x00002000,
   FM2_Bonus_Ad_Flat   = 0x00004000, // AD flat bonuses
   FM2_Bonus_Ad_Pct    = 0x00008000, // AD percentage bonuses. 0.5 = 50%
   FM2_Bonus_Ap_Flat   = 0x00010000, // AP flat bonuses
   FM2_Atks_multiplier = 0x00080000, // Attack speed multiplier. If set to 2 and champ's base attack speed is 0.600, then his new AtkSpeed becomes 1.200
   FM2_cdr             = 0x00200000, // Cooldown reduction. 0.5 = 50%
};

enum FieldMaskThree : uint32
{
   FM3_Armor_Pen = 0x00000001,
   FM3_Magic_Pen = 0x00000002
   
};

enum FieldMaskFour : uint32
{
   FM4_CurrentHp   = 0x00000001,
   FM4_CurrentMana = 0x00000002,
   FM4_MaxHp       = 0x00000004,
   FM4_MaxMp       = 0x00000008,
   FM4_exp         = 0x00000010,
   FM4_Vision1     = 0x00000100,
   FM4_Vision2     = 0x00000200,
   FM4_Speed       = 0x00000400,
   FM4_ModelSize   = 0x00000800,
   FM4_Level       = 0x00002000 //not sure how to edit this, but it is level as setting it to any value changes level to 0
};

enum FieldMaskFive : uint32
{
};

class Stats {

protected:
   std::map<uint32, float> stats[5];
   std::multimap<uint8, uint32> updatedStats;
   bool updatedHealth;
   
public:

   Stats() : updatedHealth(false) { }

   float getStat(uint8 blockId, uint32 stat) const;
   void setStat(uint8 blockId, uint32 stat, float value);

   const std::multimap<uint8, uint32>& getUpdatedStats() const { return updatedStats; }
   void clearUpdatedStats() { updatedStats.clear(); }
   
   bool isUpdatedHealth() const { return updatedHealth; }
   void clearUpdatedHealth() { updatedHealth = false; }

   virtual float getBaseAd() const {
      return getStat(MM_Two, FM2_Base_Ad);
   }
   
   virtual float getBonusAdFlat() const {
      return getStat(MM_Two, FM2_Bonus_Ad_Flat);
   }
   
   virtual float getBonusApFlat() const {
     return getStat(MM_Two, FM2_Bonus_Ap_Flat);
   }
   
   virtual float getBonusAdPct() const {
      return getStat(MM_Two, FM2_Bonus_Ad_Pct);
   }
   
   virtual float getBaseAp() const {
      return getStat(MM_Two, FM2_Base_Ap);
   }
   
   virtual float getCritChance() const {
      return getStat(MM_Two, FM2_Crit_Chance);
   }
   
   virtual float getArmor() const {
      return getStat(MM_Two, FM2_Armor);
   }
   
   virtual float getMagicArmor() const {
      return getStat(MM_Two, FM2_Magic_Armor);
   }
   
   virtual float getRange() const {
      return getStat(MM_Two, FM2_Range);
   }
   
   virtual float getCurrentHealth() const {
      return getStat(MM_Four, FM4_CurrentHp);
   }
   
   virtual float getCurrentMana() const {
      return getStat(MM_Four, FM4_CurrentMana);
   }

   virtual float getMaxHealth() const {
      return getStat(MM_Four, FM4_MaxHp);
   }
   
      virtual float getMaxMana() const {
      return getStat(MM_Four, FM4_MaxMp);
   }
   
   virtual float getHp5() {
      return getStat(MM_Two, FM2_Hp5);
   }
   
   virtual float getMana5() {
      return getStat(MM_Two, FM2_Mp5);
   }
   
   virtual float getMovementSpeed() const {
      return getStat(MM_Four, FM4_Speed);
   }
   
   virtual float getBaseAttackSpeed() const {
      return 0.625f; // TODO : figure out champion's base attack speed mask
   }
   
   virtual float getAttackSpeedMultiplier() const {
      return getStat(MM_Two, FM2_Atks_multiplier);
   }
   
      
   virtual float getGold(){
       return getStat(MM_One, FM1_Gold);
       
   }
   
      virtual float getGoldPer5(){
       return getStat(MM_One, FM1_Gold_2);
       
   }
   virtual void setCritChance(float crit) {
      return setStat(MM_Two, FM2_Crit_Chance, crit);
   }
   
   virtual void setBaseAd(float ad) {
      setStat(MM_Two, FM2_Base_Ad, ad);
   }
   
   virtual void setRange(float range) {
      setStat(MM_Two, FM2_Range, range);
   }
   
   virtual void setBonusAdFlat(float ad) {
      setStat(MM_Two, FM2_Bonus_Ad_Flat, ad);
   }
   
   virtual void setBonusApFlat(float ap) {
   setStat(MM_Two, FM2_Bonus_Ap_Flat, ap);
   }
   
   virtual void setArmor(float armor) {
      setStat(MM_Two, FM2_Armor, armor);
   }
   
   virtual void setMagicArmor(float armor) {
      setStat(MM_Two, FM2_Magic_Armor, armor);
   }
   
   virtual void setHp5(float hp5) {
      setStat(MM_Two, FM2_Hp5, hp5);
   }
   
   virtual void setMp5(float mp5) {
      setStat(MM_Two, FM2_Mp5, mp5);
   }
   
   virtual void setCurrentHealth(float health) {
      setStat(MM_Four, FM4_CurrentHp, health);
      updatedHealth = true;
   }
   
   virtual void setCurrentMana(float mana) {
      setStat(MM_Four, FM4_CurrentMana, mana);
   }
   
   virtual void setMaxMana(float mana) {
      setStat(MM_Four, FM4_MaxMp, mana);
   }

   virtual void setMaxHealth(float health) {
      setStat(MM_Four, FM4_MaxHp, health);
      updatedHealth = true;
   }
   
   virtual void setMovementSpeed(float speed) {
      setStat(MM_Four, FM4_Speed, speed);
   }
   
   virtual void setGold(float gold) {
      setStat(MM_One, FM1_Gold, gold);
   }
   
     virtual void setGoldPer5(float gold) {
      setStat(MM_One, FM1_Gold_2, gold);
   }

   virtual void setBaseAp(float AP) {
      setStat(MM_Two, FM2_Base_Ap, AP);
   }

   virtual void setExp(float EXP) {
	  setStat(MM_Four, FM4_exp, EXP);
   }
   
   
   virtual void setLevel(float level) {
	  setStat(MM_Four, FM4_Level, level);
   }

   virtual void setSize(float Size) {
	  setStat(MM_Four, FM4_ModelSize, Size);
   }

   virtual void setBaseAttackSpeed(float speed) {
   }
   
   virtual void setAttackSpeedMultiplier(float multiplier) {
      return setStat(MM_Two, FM2_Atks_multiplier, multiplier);
   }
   
   void update(int64 diff) {
      if(getHp5() > 0 && getCurrentHealth() != getMaxHealth()) {
         float newHealth = getCurrentHealth()+(getHp5()/5.f)*(diff*0.000001);
         newHealth = std::min(getMaxHealth(), newHealth);
         setCurrentHealth(newHealth);
      }
      
      if(getMana5() > 0 && getCurrentMana() != getMaxMana()) {
         float newMana = getCurrentMana()+(getMana5()/5.f)*(diff*0.000001);
         newMana = std::min(getMaxMana(), newMana);
         setCurrentMana(newMana);
      }
      if(getGoldPer5() > 0){//todo: only generate gold if time > whatever time gold starts generating
        float newGold = getGold()+(getGoldPer5()/5.f)*(diff*0.000001);
        setGold(newGold);
      }
   }
   
   /**
    * Meta-stats, relying on other stats
    */
    
    float getTotalAd() const {
      return (getBaseAd()+getBonusAdFlat())*(1+getBonusAdPct());
    }
    
    float getTotalAttackSpeed() const {
      return getBaseAttackSpeed()*getAttackSpeedMultiplier();
    }

};

#endif