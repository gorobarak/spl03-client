#include <stdlib.h>
#include <ConnectionHandler.h>

#include <iostream>
#include <mutex>
#include <thread>

class ServerReadTask {
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
    ServerReadTask(std::string taskName, ConnectionHandler& cHandler, std::mutex& mutex, bool& terminated) : taskName(taskName), cHandler(cHandler), mutex(mutex), terminated(terminated) {}

    void run() {
        while (!isTerminated()) {
            //std::cout<< "started server read" << std::endl;//TODO
            std::string ans;
            if (!cHandler.getLine(ans)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }


            std::cout << ans << std::endl;//TODO should ans be modified?

            if (ans == "ACK 4") {//ack for logout request - should terminate
                std::lock_guard<std::mutex> lock(mutex);
                terminated = true;
            }
        }
    }
};

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
        while (!isTerminated()) {
            const short bufsize = 1024;
            char buf[bufsize];
            std::cin.getline(buf, bufsize);
            std::string line(buf); //input received from kb
            //int len=line.length();
            if (!cHandler.sendLine(line)) {
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

    //std::cout << " connected" << std::endl;//TODO

    std::mutex mutex;
    bool terminated = false;
    KeyboardReadTask kbTask("keyboard", connectionHandler, mutex, terminated);
    ServerReadTask serverTask("serverRead", connectionHandler, mutex, terminated);

    std::thread t1(&KeyboardReadTask::run, &kbTask);
    std::thread t2(&ServerReadTask::run, &serverTask);

    t1.join();
    t2.join();

    connectionHandler.close();
    std::cout << "Exiting...\n" << std::endl;
    return 0;
}