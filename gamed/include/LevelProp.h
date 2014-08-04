#ifndef _LEVELPROP_H
#define _LEVELPROP_H

#include "Object.h"

class LevelProp : public Object {

private:
   std::string name;
   std::string type;
   float z;

public:
   LevelProp(Map* map, uint32 id, float x, float y, float z, const std::string& name, const std::string& type) : Object(map, id, x, y, 0), z(z), name(name), type(type) { }
   float getZ() const { return z; }

   float getMoveSpeed() const override { return 0.f; }
   
   const std::string& getName() const { return name; }
   const std::string& getType() const { return type; }

};


#endif