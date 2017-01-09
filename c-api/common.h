#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <math.h>

#define MAX_COLOR 255

void error(lua_State *L, const char* fmt, ...){
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

float getfield(lua_State *L, const char *key){
    float result;
    /*
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    */
    lua_getfield(L, -1, key);
    if(!lua_isnumber(L, -1))
        error(L, "invalid component int background color");

    result = (float)lua_tonumber(L, -1)*MAX_COLOR;
    lua_pop(L, 1);
    return result; 
}

void setfield(lua_State *L, const char *index, int value){
    /*
    lua_pushstring(L, index);
    lua_pushnumber(L, (double)value/MAX_COLOR);
    lua_settable(L, -3);
    */
    lua_pushnumber(L, (double)value/MAX_COLOR);
    lua_setfield(L, -2, index);
}

static int l_sin(lua_State *L){
    float d = luaL_checknumber(L, 1);
    printf("c l_sin para %f \n", d);
    lua_pushnumber(L, sin(d));
    return 1;
}
