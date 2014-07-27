#ifndef __TURRET_H
#define __TURRET_H

#include "Unit.h"

class Turret : public Unit {
private:
   std::string name;

public:
   Turret(Map* map, uint32 id, const std::string& name, float x = 0, float y = 0) : Unit(map, id, new Stats(), x, y, 0), name(name)  { }
   const std::string& getName() const { return name; }

};

#endif