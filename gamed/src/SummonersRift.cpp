#include "SummonersRift.h"
#include "Turret.h"
#include "Game.h"
#include "LevelProp.h"

using namespace std;

SummonersRift::SummonersRift(Game* game) : Map(game) {
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_R_03_A", 10097.62, 808.73, 2550, 156, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_R_02_A", 6512.53, 1262.62, 2550, 170, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_07_A", 3747.26, 1041.04, 2550, 190, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_R_03_A", 0, 0, 2550, 156, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_R_02_A", 0, 0, 2550, 170, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_R_01_A", 0, 0, 2550, 190, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_05_A", 5435.02, 6179.10, 2550, 156, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_04_A", 4633.66, 4591.91, 2550, 170, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_03_A", 3233.99, 3447.24, 2550, 190, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_01_A", 1341.63, 2029.98, 2425, 180, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_02_A", 1768.19, 1589.47, 2425, 180, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_C_05_A", 0, 0, 2550, 156, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_C_04_A", 0, 0, 2550, 170, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_C_03_A", 0, 0, 2550, 190, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_C_01_A", 0, 0, 2425, 180, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_C_02_A", 0, 0, 2425, 180, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_OrderTurretShrine_A", -236.05, -53.32, 9999, 999, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_ChaosTurretShrine_A", 0, 0, 9999, 999, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_L_03_A", 574.66, 10220.47, 2550, 156, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_L_02_A", 1106.26, 6485.25, 2550, 170, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T1_C_06_A", 802.81, 4052.36, 2550, 190, 0));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_L_03_A", 0, 0, 2550, 156, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_L_02_A", 0, 0, 2550, 170, 1));
   addObject(new Turret(this, GetNewNetID(), "@Turret_T2_L_01_A", 0, 0, 2550, 190, 1));
   
   addObject(new LevelProp(this, GetNewNetID(), 12465, 14422.257f, 101, "LevelProp_Yonkey", "Yonkey"));
   addObject(new LevelProp(this, GetNewNetID(), -76, 1769.1589f, 94, "LevelProp_Yonkey1", "Yonkey"));
   addObject(new LevelProp(this, GetNewNetID(), 13374, 14245.673f, 194, "LevelProp_ShopMale", "ShopMale"));
   addObject(new LevelProp(this, GetNewNetID(), -99, 855.6632f, 191, "LevelProp_ShopMale1", "ShopMale"));
}

void SummonersRift::update(long long diff) {
   Map::update(diff);
   // TODO : add in here minion spawning every X seconds, jungle camp spawning [...]
}
