CC = g++
CFLAGS = -g -Wall -std=c++11
L10N_LANG = ENG #localization language

all: ImageServerTest ImageServer

clean:
	rm ImageServerTest ImageServer.o

ImageServer: ImageServer.cpp ImageServer.h
	$(CC) $(CFLAGS) -c ImageServer.cpp -o ImageServer.o

ImageServerTest: ImageServer ImageServerTest.cpp
	$(CC) $(CFLAGS) -DL10N_LANG=$(L10N_LANG) \
		ImageServerTest.cpp ImageServer.o -o ImageServerTest


