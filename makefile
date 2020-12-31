CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system

all: EchoClient BGRSclient
	g++ -o bin/echoExample bin/ConnectionHandler.o bin/echoClient.o  bin/BGRSclient.o $(LDFLAGS)

BGRSclient: bin/ConnectionHandler.o bin/BGRSclient.o

EchoClient: bin/ConnectionHandler.o bin/echoClient.o
	
bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/echoClient.o: src/echoClient.cpp
	g++ $(CFLAGS) -o bin/echoClient.o src/echoClient.cpp

bin/BGRSclient.o: src/BGRSclient.cpp
	g++ $(CFLAGS) -o bin/BGRSclient.o src/BGRSclient.cpp
.PHONY: clean
clean:
	rm -f bin/*
