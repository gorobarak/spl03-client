#include <stdlib.h>
#include <ConnectionHandler.h>

#include <iostream>
#include <mutex>
#include <thread>

class KeyboardReadTask {
private:
    std::string taskName;
    ConnectionHandler& cHandler;
    std::mutex& mutex;
    bool& terminated;

    bool isTerminated(){
        std::lock_guard<std::mutex> lock(mutex);
        return terminated;
    }

public:
    KeyboardReadTask(std::string taskName, ConnectionHandler& cHandler, std::mutex& mutex, bool& terminated) : taskName(taskName), cHandler(cHandler), mutex(mutex), terminated(terminated) {}

    void run() {
        while (true) {
            const short bufsize = 1024;
            char buf[bufsize];
            std::cin.getline(buf, bufsize);
            std::string line(buf); //input received from kb
            int len=line.length();
            if (!ConnectionHandler.sendLine(line)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }

        }
    }

};



int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    std::mutex mutex;
    bool terminated = false;
    KeyboardReadTask kbTask("keyboard", connectionHandler, mutex, terminated);
    ServerReadTask serverTask("serverRead", connectionHandler, mutex, terminated);

    thread::Thread

    std::cout << "Exiting...\n" << std::endl;

}