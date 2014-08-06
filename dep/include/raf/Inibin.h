#ifndef __H_INIBIN
#define __H_INIBIN

#include <map>
#include <string>
#include <stdio.h>

#include "MemoryReader.h"

using namespace std;

struct Value {
   Value() : floatV(0), boolV(0) {
   
   }

   float floatV;
   bool boolV;
   std::string stringV;
};

class Inibin {
public:
   Inibin(const std::vector<unsigned char>& file) : buffer(file) {
      
      size = buffer.size();
      buffer >> version >> oldLength >> bitmask;
      
      uint16 nbKeys;
      
      if(bitmask & 0x0001) {
         buffer >> nbKeys;
         readUint32Values(readKeys(nbKeys));
      }
      
      if(bitmask & 0x0002) {
         buffer >> nbKeys;
         readFloatValues(readKeys(nbKeys));
      }
      
      if(bitmask & 0x0004) {
         buffer >> nbKeys;
         readUint10Values(readKeys(nbKeys));
      }
      
      if(bitmask & 0x0008) {
         buffer >> nbKeys;
         readUint16Values(readKeys(nbKeys));
      }
      
      if(bitmask & 0x0010) {
         buffer >> nbKeys;
         readUint8Values(readKeys(nbKeys));
      }
      
      if(bitmask & 0x0020) {
         buffer >> nbKeys;
         readBooleanValues(readKeys(nbKeys));
      }
      
      if(bitmask & 0x1000) {
         buffer >> nbKeys;
         readStringValues(readKeys(nbKeys));
      }
   }
   
   std::vector<uint32> readKeys(uint8 nbKeys) {
      std::vector<uint32> toReturn;
      
      for(uint8 i = 0; i < nbKeys; ++i) {
         uint32 key;
         buffer >> key;
         toReturn.push_back(key);
      }
      
      return toReturn;
   }
   
   static uint32 getKeyHash(const std::string& sectionName, const std::string& varName) {
      uint32 hash = 0;
      
      for(char c : sectionName) {
         hash = tolower(c) + 65599 * hash;
      }

      hash = (65599 * hash + 42);
      for(char c : varName) {
         hash = tolower(c) + 65599 * hash;
      }

      return hash;
   }
   
   void readUint32Values(const std::vector<uint32>& keys) {
      for(uint32 key : keys) {
         uint32 v;
         buffer >> v;
      
         Value value;
         value.floatV = v;
         values[key] = value;
      }
   }
   
   void readUint16Values(const std::vector<uint32>& keys) {
      for(uint32 key : keys) {
         uint16 v;
         buffer >> v;
         
         Value value;
         value.floatV = v;
         values[key] = value;
      }
   }
   
   void readUint8Values(const std::vector<uint32>& keys) {
      for(uint32 key : keys) {
         uint8 v;
         buffer >> v;
                  
         Value value;
         value.floatV = v;
         values[key] = value;
      }
   }
   
   void readUint10Values(const std::vector<uint32>& keys) {
      for(uint32 key : keys) {
         uint8 v;
         buffer >> v;
         Value value;
         value.floatV = v*0.1f;
         values[key] = value;
      }
   }
   
   void readFloatValues(const std::vector<uint32>& keys) {
      for(uint32 key : keys) {
         Value value;
         buffer >> value.floatV;
         
         values[key] = value;
      }
   }
   
   void readBooleanValues(const std::vector<uint32>& keys) {      
      int index = 0;
      uint8 boolean;
      
      for(uint32 key : keys) {
         Value value;
      
         if(index % 8 == 0) {
            buffer >> boolean;
         } else {
            boolean >>= 1;
         }
         
         value.boolV = boolean & 0x01;
         values[key] = value;
         ++index;
      }
   }
   
   void readStringValues(const std::vector<uint32>& keys) {
      uint32 i = 1;
      for(uint32 key : keys) {
         Value value;
  
         uint16 offset;
         
         buffer >> offset;
         value.stringV = reinterpret_cast<const char*>(&buffer.getBytes()[offset+keys.size()*2-i*2]);
         
         values[key] = value;
         ++i;
      }
   }
         
   float getFloatValue(const std::string& sectionName, const std::string& varName) {
      if(values[getKeyHash(sectionName, varName)].floatV == 0 && values[getKeyHash(sectionName, varName)].stringV[0] != 0) {
         return atof(values[getKeyHash(sectionName, varName)].stringV.c_str());
      }
      return values[getKeyHash(sectionName, varName)].floatV;
   }
   
   bool getBoolValue(const std::string& sectionName, const std::string& varName) {
      return values[getKeyHash(sectionName, varName)].boolV;
   }
   
   const std::string& getStringValue(const std::string& sectionName, const std::string& varName) {
      return values[getKeyHash(sectionName, varName)].stringV;
   }

private:
   
   std::map<uint32, Value> values;
   MemoryReader buffer;
   uint8 version;
   uint16 oldLength;
   uint16 bitmask;
   uint32 size;


};




#endif