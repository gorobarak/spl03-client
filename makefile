CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lboost_thread -pthread

all: BGRSclient
	g++ -o bin/BGRSclient bin/ConnectionHandler.o  bin/BGRSclient.o bin/BGRSencoderDecoder.o $(LDFLAGS)

BGRSclient: bin/ConnectionHandler.o bin/BGRSclient.o bin/BGRSencoderDecoder.o

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/BGRSclient.o: src/BGRSclient.cpp
	g++ $(CFLAGS) -o bin/BGRSclient.o src/BGRSclient.cpp

bin/BGRSencoderDecoder.o: src/BGRSencoderDecoder.cpp
	g++ $(CFLAGS) -o bin/BGRSencoderDecoder.o src/BGRSencoderDecoder.cpp

.PHONY: clean
clean:
	rm -f bin/*
