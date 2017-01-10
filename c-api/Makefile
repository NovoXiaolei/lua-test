CC = gcc
PLATS= macosx linux
LUA_INC := /usr/local/include

all : test window

test: test1.c
	$(CC) -o test  test1.c  -I/usr/local/include -L/usr/local/lua/lib /usr/local/lib/liblua.a -llua -ldl -lm -Wall

window: window.c
	$(CC) -o window window.c  -I/usr/local/include -L/usr/local/lua/lib /usr/local/lib/liblua.a -llua -ldl -lm -Wall

clean:
	-rm -f test
	-rm -f window	

