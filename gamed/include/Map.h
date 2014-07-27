#ifndef _MAP_H
#define _MAP_H

#include <map>
#include <vector>

#include "stdafx.h"
#include "Object.h"

class Game;

class Map {

private:
   std::map<uint32, Object*> objects;
   Game* game;
   
public:
   Map(Game* game) : game(game) { }
   
   virtual ~Map() { }
   virtual void update(long long diff);
   
   Object* getObjectById(uint32 id);
   void addObject(Object* o);
   
   Game* getGame() const { return game; }
   
   const std::map<uint32, Object*>& getObjects() { return objects; }

};

#endif