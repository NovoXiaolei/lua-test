#include <stdio.h>
#include <string.h>
/*
#include <lua.h>
#include <luaxlib.h>
#include <lualib.h>
*/
#include "common.h"

struct ColorTable{
    char *name;
    unsigned char red, green, blue;
} colortable[] = {
    {"WHITE", MAX_COLOR, MAX_COLOR, MAX_COLOR},
    {"RED", MAX_COLOR, 0, 0},
    {"GREEN", 0, MAX_COLOR, 0},
    {"BLUE", 0, 0, MAX_COLOR},
    {NULL, 0, 0, 0}
};

void load(lua_State *L, const char *fname, int *w, int *h);
void load_test(lua_State *L, const char* fname);
void setcolor(lua_State *L, struct ColorTable *ct);
double f(lua_State *L, double x, double y);

int main(int argc, char *argv[]){
    const char* file = argv[1];
    printf("file name %s\n", file);

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    int w, h;
    load(L, file, &w, &h); 
    printf(" width = %d, height = %d  \n", w, h);

    int i = 0;
    while(colortable[i].name!=NULL){
        setcolor(L, &colortable[i++]);
    }
    
    lua_pushcfunction(L, l_sin);
    lua_setglobal(L, "mysin");

    load_test(L, "test.lua");
    double z = f(L, 100, 101);
    printf("call 'f' , return %lf ", z);

    lua_close(L);
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

    lua_getglobal(L, "background");
    if(!lua_istable(L, -1))
        error(L, " 'background' is not a table");

    float red = getfield(L, "r");
    float green = getfield(L, "g");
    float blue = getfield(L, "b"); 
    printf(" red = %.2f, green = %.2f, blue = %.2f ", red, green, blue);     
}

void load_test(lua_State *L, const char* fname){
    if(luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0))
        error(L, "cannot run config.file: %s", lua_tostring(L, -1));
}

void setcolor(lua_State *L, struct ColorTable *ct){
    //创建一个table并压入栈中
    lua_newtable(L);
    setfield(L, "r", ct->red);
    setfield(L, "g", ct->green);
    setfield(L, "b", ct->blue);
    lua_setglobal(L, ct->name);
}


double f(lua_State *L, double x, double y){
    double z;

    lua_getglobal(L, "f");
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);

    //两个参数， 一个结果
    //第四个是错误函数的索引
    if(lua_pcall(L, 2, 1, 0)!=0)
        error(L, "error running function 'f':%s", lua_tostring(L, -1));

    if(!lua_isnumber(L, -1)){
        error(L, "function 'f' must return a number");
    }
    z = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return z;
}
