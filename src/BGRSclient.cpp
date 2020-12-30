#include <stdlib.h>
#include <connectionHandler.h>

#include <iostream>
#include <mutex>
#include <thread>

class KeyboardReadTask {
private:
    connectionHandler& cHandler;
    std::mutex& mutex;
    bool& terminated;

    bool isTerminated(){
        std::lock_guard<std::mutex> lock(mutex);
        return terminated;
    }

public:
    KeyboardReadTask(connectionHandler& cHandler, std::mutex& mutex, bool& terminated) : cHandler(cHandler), mutex(mutex), terminated(terminated) {}

    void run() {
        while (true) {
            const short bufsize = 1024;
            char buf[bufsize];
            std::cin.getline(buf, bufsize);
            std::string line(buf); //input received from kb
            int len=line.length();
            if (!connectionHandler.sendLine(line)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }

        }
    }

};