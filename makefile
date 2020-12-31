CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system

all: EchoClient BGRSclient
	g++ -o bin/echoExample bin/ConnectionHandler.o bin/echoClient.o  bin/BGRSclient.o bin/BGRSencoderDecoder.o $(LDFLAGS)

BGRSclient: bin/ConnectionHandler.o bin/BGRSclient.o bin/BGRSencoderDecoder.o

EchoClient: bin/ConnectionHandler.o bin/echoClient.o
	
bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/echoClient.o: src/echoClient.cpp
	g++ $(CFLAGS) -o bin/echoClient.o src/echoClient.cpp

bin/BGRSclient.o: src/BGRSclient.cpp
	g++ $(CFLAGS) -o bin/BGRSclient.o src/BGRSclient.cpp

bin/BGRSencoderDecoder.o: src/BGRSencoderDecoder.cpp
	g++ $(CFLAGS) -o bin/BGRSencoderDecoder.o src/BGRSencoderDecoder.cpp

.PHONY: clean
clean:
	rm -f bin/*
