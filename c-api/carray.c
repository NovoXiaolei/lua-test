#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define BITS_PER_WORD (CHAR_BIT*sizeof(unsigned int))
#define I_WORD(i)   ( (unsigned int) (i) / BITS_PER_WORD)
#define I_BIT(i)    (1 << ((unsigned int)(i)%BITS_PER_WORD))


typedef struct NumArray{
    int size;
    unsigned int values[1];
}NumArray;

#define checkarray(L) \
    (NumArray*)luaL_checkudata(L, 1, "LuaBook.array")

static unsigned int *getindex(lua_State *L, unsigned int *mask);
static int newarray(lua_State *L){
    printf("new array"); 
    int i, n;
    size_t nbytes;
    NumArray *a;

    n = luaL_checkinteger(L,1);
    luaL_argcheck(L, n>=1, 1,  "invalid size");
    nbytes = sizeof(NumArray) + I_WORD(n-1)*sizeof(unsigned int);
    a = (NumArray*)lua_newuserdata(L, nbytes);

    a->size = n;
    for(i = 0; i<=I_WORD(n-1); i++)
        a->values[i] = 0;

    luaL_getmetatable(L, "LuaBook.array");
    //从栈中弹出一个table, 并将其设为指定索引上对象的元表
    lua_setmetatable(L, -2);

    return 1;
}

static int setarray(lua_State *L){
    printf("set array"); 
    /*
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    int index = luaL_checkinteger(L, 2)-1;
    luaL_checkany(L, 3);

    luaL_argcheck(L, a!=NULL, 1, " 'array' expected ");
    luaL_argcheck(L, 0<=index && index < a->size, 2, "index out of range");

    if(lua_toboolean(L, 3))
        a->values[I_WORD(index)] |= I_BIT(index);
    else
        a->values[I_WORD(index)] &= ~I_BIT(index);
    return 0;
    */
    unsigned int mask;
    unsigned int *entry = getindex(L, &mask);
    luaL_checkany(L, 3);
    if(lua_toboolean(L, 3))
        *entry |= mask;
    else
        *entry &= ~mask;

    return 0;
}

static int getarray(lua_State *L){
    printf("get array");
    /*
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    int index = luaL_checkinteger(L, 2) -1;

    luaL_argcheck(L, a != NULL, 1, " 'array' expected");
    luaL_argcheck(L, 0<=index && index < a->size, 2, "index out of range");

    lua_pushboolean(L, a->values[I_WORD(index)] & I_BIT(index));
    return 1;
    */
}

static unsigned int *getindex(lua_State *L, unsigned int *mask){
    NumArray *a = checkarray(L);
    int index = luaL_checkinteger(L, 2)-1;

    luaL_argcheck(L, 0<=index && index < a->size, 2, "index out of range");
    *mask = I_BIT(index);
    return &a->values[I_WORD(index)];
}

static int getsize(lua_State *L){
    printf("get size");
    //NumArray *a = (NumArray *)lua_touserdata(L, 1);
    NumArray *a = checkarray(L);
    luaL_argcheck(L, a!=NULL, 1, "'array' expected ");
    lua_pushinteger(L, a->size);
    return 1;
}

static int hello_c(lua_State *L){
    const char* from_lua = lua_tostring(L, 1);
    printf("lua:%s\n", from_lua);
    lua_pushstring(L, "hi lua");
    return 1;
}

static const struct luaL_Reg arraylib[]={
    {"new", newarray},
    {"set", setarray},
    {"get", getarray},
    {"size", getsize},
    {"hello_c", hello_c},
    {NULL, NULL}
};

int luaopen_myarray(lua_State *L){
    printf("start register array");
    //创建一个新的table用作元表， 并将其压入栈顶，然后将这个table与注册表中指定的名字关联起来
    luaL_newmetatable(L, "LuaBook.array");
    luaL_newlib(L, arraylib);
    printf("end register array");
    return 1;
}
