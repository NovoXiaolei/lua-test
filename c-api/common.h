#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <math.h>
#include <dirent.h>
#include <errno.h>

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

static int l_dir(lua_State *L){
    DIR* dir;
    struct dirent *entry;
    int i;

    const char *path = luaL_checkstring(L, 1);
    printf("scan path = %s \n", path);

    dir = opendir(path);
    if(dir == NULL){
        lua_pushnil(L);
        lua_pushstring(L, strerror(errno));
        return 2;
    }

    lua_newtable(L);
    i = 1;
    while((entry = readdir(dir)) != NULL){
        lua_pushnumber(L, i++);
        lua_pushstring(L, entry->d_name);
        lua_settable(L, -3);
    }

    closedir(dir);
    return 1;
}

static int l_map(lua_State *L){
    int i, n;
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);

    //获得table的大小
    n = lua_objlen(L, 1);
    
    for(i = 1; i<=n;i++){
        lua_pushvalue(L, 2);
        lua_rawgeti(L, 1, i);
        lua_call(L, 1, 1);
        lua_rawseti(L, 1, i);
    }
    return 0;
}
