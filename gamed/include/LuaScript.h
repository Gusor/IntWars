
#include <sol.hpp>
#include <stdafx.h>

#ifndef LUASCRIPT_H
#define	LUASCRIPT_H
class LuaScript{
private:

public:
    LuaScript();
    
    void loadScript(std::string location);
    sol::table getTable(std::string name);
    void setFunction();
    sol::state lua;
    
    //sol::state getLua(){return lua;}
};
    



#endif	/* LUASCRIPT_H */

