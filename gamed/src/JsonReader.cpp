#include "JsonReader.h"
#include <fstream>
#include <streambuf>
#include <sstream>
#include <iostream>


#define getInt(a,i) a.get(i, 0.0f).asInt();
#define getFloat(a,i) a.get(i, 0.0f).asFloat();
#define getBool(a,i) a.get(i, 0.0f).asBool();

static std::string convertInt(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}


JsonReader::JsonReader(int itemId){
    
    std::string itemInString = convertInt(itemId);

    
   std::ifstream t("../../data/item.json");
   std::string str((std::istreambuf_iterator<char>(t)),
   std::istreambuf_iterator<char>());


 Json::Value rootValue;
 Json::Reader reader;
 bool parsedSuccess = reader.parse(str, 
                                   rootValue, 
                                   false);
 
 if(parsedSuccess){
     printf("Found JSON file\n");
 }else{
     printf("Failed to find json file\n");
 }
 

 
   dataRoot = rootValue["data"][itemInString]; //?????
  
    //TODO: support item recipes
  

    Json::Value goldRoot = dataRoot["gold"];
       
    int base = goldRoot.get("base", -1).asInt();
    gold = (float)goldRoot.get("total", -1).asInt();
        
    int sellPrice = goldRoot.get("sell", -1).asInt();
    
    bool purchasable = goldRoot.get("purchasable", false).asBool();
    printf("Cost %f \n", gold);
  
    printf("Total cost %i \n", gold);
    printf("Sellprice %i \n", sellPrice);
    
}

void JsonReader::readItemStats(Stats* championStats){
    
        
    Json::Value stats = dataRoot["stats"];
    
    int bonusMs = getInt(stats, "FlatMovementSpeedMod");//stats.get("FlatMovementSpeedMod", 0).asInt();
    
    int bonusHp = getInt(stats, "FlatHPPoolMod");
    
    int bonusMana = getInt(stats, "FlatMagicDamageMod");
    
    int bonusAd = getInt(stats, "FlatPhysicalDamageMod");
    
    int bonusArmor = getInt(stats, "FlatArmorMod");
    
    float bonusCritChance = getFloat(stats, "FlatCritChanceMod");
    
    float bonusAttackSpeed = getFloat(stats, "PercentAttackSpeedMod");
    
    float bonusAp = getInt(stats, "FlatMagicDamageMod");
    
    float bonusMr = getInt(stats, "FlatSpellBlockMod");
    
    float bonusManaRegen = getFloat(stats, "FlatMPRegenMod");
    
    float bonusHpRegen = getFloat(stats, "FlatHPRegenMod");
    


    
    championStats->setArmor(championStats->getArmor() + bonusArmor);
    
    championStats->setMagicArmor(championStats->getMagicArmor() + bonusMr);
    
    championStats->setBonusAdFlat(championStats->getBonusAdFlat() + bonusAd);
    

    
    championStats->setBonusApFlat(championStats->getBonusApFlat() + bonusAp);
    
    championStats->setMovementSpeed(championStats->getMovementSpeed() + (float)bonusMs);
    
    printf("Movement speed total:%f", (championStats->getMovementSpeed() + (float)bonusMs));
    
    championStats->setAttackSpeedMultiplier(championStats->getAttackSpeedMultiplier() + bonusAttackSpeed);
    
    championStats->setMaxHealth(championStats->getMaxHealth() + bonusHp);
    championStats->setCurrentHealth(championStats->getCurrentHealth() + bonusHp);
    
        
    championStats->setMaxMana(championStats->getMaxMana() + bonusMana);
    championStats->setCurrentMana(championStats->getCurrentMana() + bonusMana);
    
    
    championStats->setCritChance(championStats->getCritChance() + bonusCritChance);
    
    printf("Bonus AD: %i \n", bonusAd);
    
    printf("Bonus ms: %i \n", bonusMs);
    
    printf("Bonus mana: %f \n", bonusManaRegen);
    
    printf("Bonus hpRegen: %f \n", bonusHpRegen);
    
    printf("Bonus HP: %f \n", bonusHpRegen);
    
    float newGold = championStats->getGold() - gold;
    
    
    championStats->setGold(newGold);

    

    
}


