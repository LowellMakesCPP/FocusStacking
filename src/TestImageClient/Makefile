CC = g++
CFLAGS = -g -Wall -std=c++11 
CFLAGS += -lboost_system -lboost_filesystem -lboost_date_time
CFLAGS += -lboost_regex -pthread

all: TestImageClient TestImageClientPing TestImageClientPingRegression

clean:
	rm TestImageClient TestImageClientPing TestImageClientPingRegression

TestImageClient: TestImageClient.cpp
	$(CC) $(CFLAGS) TestImageClient.cpp -o TestImageClient

TestImageClientPing: TestImageClientPing.cpp
	$(CC) $(CFLAGS) TestImageClientPing.cpp -o TestImageClientPing

TestImageClientPingRegression: TestImageClientPingRegression.cpp
	$(CC) $(CFLAGS) TestImageClientPingRegression.cpp -o \
	TestImageClientPingRegression


