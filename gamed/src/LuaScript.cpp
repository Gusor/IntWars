#include "LuaScript.h"
#include "sol/state.hpp"
LuaScript::LuaScript(){
    lua.open_libraries(sol::lib::base, sol::lib::table, sol::lib::package, sol::lib::math, sol::lib::debug);
    
}

sol::table LuaScript::getTable(std::string name){
    return lua.get<sol::table>(name);
}


void LuaScript::loadScript(std::string location){
        lua.open_file(location);  
}

