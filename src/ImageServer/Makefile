CC = g++
CFLAGS = -g -Wall -std=c++11

all: ImageServerTest ImageServer

clean:
	rm ImageServerTest ImageServer.o

ImageServer: ImageServer.cpp ImageServer.h
	$(CC) $(CFLAGS) -c ImageServer.cpp -o ImageServer.o

ImageServerTest: ImageServer ImageServerTest.cpp
	$(CC) $(CFLAGS) ImageServerTest.cpp ImageServer.o -o ImageServerTest


