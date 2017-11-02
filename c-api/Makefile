CC = gcc -v
PLATS= macosx linux
LUA_INC := ./lua-5.3.4/src/ 
SHARED := -fPIC --shared
LIB := ./lua-5.3.4/src/lua

all : test testupvalue.so

test: test1.c
	$(CC) -o test  test1.c  -I$(LUA_INC)  -llua -ldl -lm -Wall

testupvalue.so: lua-testupvalue.c  
	$(CC) $(SHARED) $^ -o $@  -I$(LUA_INC) -l./lua-5.3.4/src/lua.o -ldl -lm -Wall

clean:
	-rm -f test
	-rm -f *.so

