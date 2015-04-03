CC = g++
CFLAGS = -g -Wall -std=c++11

# localization file and language
L10N_LANG = DAN #ENG
L10N_FILE = ResourceStr$(strip $(L10N_LANG)).inc

all: ImageServerTest ImageServer

clean:
	rm ImageServerTest ImageServer.o

ImageServer: ImageServer.cpp ImageServer.h
	$(CC) $(CFLAGS) -DL10N_LANG=$(L10N_FILE) \
			-c ImageServer.cpp -o ImageServer.o

ImageServerTest: ImageServer ImageServerTest.cpp
	$(CC) $(CFLAGS) ImageServerTest.cpp ImageServer.o -o ImageServerTest


