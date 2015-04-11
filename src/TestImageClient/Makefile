CC = g++
CFLAGS = -g -Wall -std=c++11 
CFLAGS += -lboost_system -lboost_filesystem -lboost_date_time
CFLAGS += -lboost_regex

all: TestImageClient

clean:
	rm TestImageClient

TestImageClient: TestImageClient.cpp
	$(CC) $(CFLAGS) TestImageClient.cpp -o TestImageClient

