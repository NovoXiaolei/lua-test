CC = gcc
PLATS= macosx linux
LUA_INC := /usr/local/include

all : test window userdata myarray.so

test: test1.c
	$(CC) -o test  test1.c  -I/usr/local/include -L/usr/local/lua/lib /usr/local/lib/liblua.a -llua -ldl -lm -Wall

window: window.c
	$(CC) -o window window.c  -I/usr/local/include -L/usr/local/lua/lib /usr/local/lib/liblua.a -llua -ldl -lm -Wall

userdata: userdata.c
	$(CC) -g  -o userdata userdata.c  -I/usr/local/include -L/usr/local/lua/lib /usr/local/lib/liblua.a -llua -ldl -lm -Wall

myarray.so: carray.c
	$(CC) -O2 -fpic -c -o carray.o carray.c 
	$(CC) -O -shared -fpic -o myarray.so carray.o

clean:
	-rm -f test
	-rm -f window	
	-rm -f userdata
	-rm -f myarray.so

