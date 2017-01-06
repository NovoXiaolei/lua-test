#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void load(lua_State *L, const char *fname, int *w, int *h);

int main(int argc, char *argv[]){
    const char* file = argv[1];
    printf("file name %s", file);
    return 0;
}

void load(lua_State *L, const char *fname, int *w, int *h){
    if(luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run config.file: %s", lua_tostring(L, -1));
    //压入了-2这个位置
    lua_getglobal(L, "width");
    //压入了-1这个位置
    lua_getglobal(L, "height");
    
    if(!lua_isnumber(L, -2))
        error(L, " 'width' should be a number \n");

    if(!lua_isnumber(L, -1))
        error(L, " 'height' should be a number \n");

    *w = lua_tointeger(L, -2);
    *h = lua_tointeger(L, -1);

}