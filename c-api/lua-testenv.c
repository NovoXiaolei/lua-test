#include <stdio.h>
#include <stdlib.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static int setValue(lua_State *L){
    luaL_checkstring(L, -1);
    lua_pushvalue(L, -1);
    //貌似在5.3中这个常量已经删除
    lua_setfield(L, LUA_ENVIRONINDEX, "k1");
    return 0;
}

static int getValue(lua_State *L){
    lua_getfield(L, LUA_ENVIRONINDEX, "k1");
    return 1;
}

int luaopen_testenv(lua_State* L){
    luaL_Reg l[] = {
        {"setValue", setValue},
        {"getValue", getValue},
        {NULL, NULL}
    };
    luaL_checkversion(L);
    luaL_newlib(L, l);
    return 1;
}
