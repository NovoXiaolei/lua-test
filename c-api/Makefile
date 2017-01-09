CC = gcc
PLATS= macosx linux
LUA_INC := /usr/local/include

all : test window

test: test1.c
	#mac
	$(CC) -o test1  test1.c -I${LUA_INC} -llua
#centos	
#	$(CC) -lm -o test1  test1.c /usr/local/lib/liblua.a -ldl

window: window.c
	$(CC) -o window window.c -I $(LUA_INC) -llua

clean:
	-rm -f test
	-rm -f window	

