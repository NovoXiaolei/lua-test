CC = gcc
LUA_INC := /usr/local/include

all : test window

test: test1.c
	$(CC) -o test1  test1.c -I${LUA_INC} -llua

window: window.c
	$(CC) -o window window.c -I $(LUA_INC) -llua

clean:
	-rm -f test
	-rm -f window	

