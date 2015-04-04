CC = g++
CFLAGS = -g -Wall -std=c++11 
CFLAGS += -lboost_system -lboost_filesystem -lboost_date_time
CFLAGS += -lboost_regex

# localization file and language
L10N_LANG = ENG #DAN #FRA
L10N_FILE = ResourceStr$(strip $(L10N_LANG)).inc

all: ImageServerTest ImageServer

clean:
	rm ImageServerTest ImageServer.o

ImageServer: ImageServer.cpp ImageServer.h
	$(CC) $(CFLAGS) -DL10N_LANG=$(L10N_FILE) \
			-c ImageServer.cpp -o ImageServer.o

ImageServerTest: ImageServer ImageServerTest.cpp
	$(CC) $(CFLAGS) ImageServerTest.cpp ImageServer.o -o ImageServerTest


