#include <stdlib.h>
#include <ConnectionHandler.h>

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

class ServerReadTask {
private:
    std::string taskName;
    ConnectionHandler& cHandler;
    std::mutex& mutex;
    bool& terminated;
    std::condition_variable& cv;

    bool isTerminated(){
        std::lock_guard<std::mutex> lock(mutex);
        return terminated;
    }

public:
    ServerReadTask(std::string taskName, ConnectionHandler& cHandler, std::mutex& mutex, bool& terminated, std::condition_variable& cv) :
        taskName(taskName), cHandler(cHandler), mutex(mutex), terminated(terminated), cv(cv) {}

    void run() {
        while (!isTerminated()) {
            std::string ans;
            if (!cHandler.getLine(ans)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }


            std::cout << ans << std::endl;

            if (ans == "ACK 4" && isTerminated()) {//ack for logout request - should terminate
                cv.notify_all();
                break;
            }
            else if (ans == "ERROR 4" && isTerminated()) {
                mutex.lock();
                terminated = false;
                mutex.unlock();
                cv.notify_all();
            }
        }
        std::this_thread::yield();
    }
};

class KeyboardReadTask {
private:
    std::string taskName;
    ConnectionHandler& cHandler;
    std::mutex& mutex;
    bool& terminated;
    std::condition_variable& cv;
    std::unique_lock<std::mutex>& waitOn;

    bool isTerminated(){
        std::lock_guard<std::mutex> lock(mutex);
        return terminated;
    }

public:
    KeyboardReadTask(std::string taskName, ConnectionHandler& cHandler, std::mutex& mutex, bool& terminated, std::condition_variable& cv, std::unique_lock<std::mutex>& waitOn) :
            taskName(taskName), cHandler(cHandler), mutex(mutex), terminated(terminated), cv(cv), waitOn(waitOn)  {}

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
            if (line == "LOGOUT"){
                mutex.lock();
                terminated = true;
                mutex.unlock();
                cv.wait(waitOn);
                if(terminated) break;
            }
        }
        std::this_thread::yield();
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
    std::mutex notify;
    bool terminated = false;
    std::condition_variable cv;
    std::unique_lock<std::mutex> waitOn(notify);
    KeyboardReadTask kbTask("keyboard", connectionHandler, mutex, terminated, cv, waitOn);
    ServerReadTask serverTask("serverRead", connectionHandler, mutex, terminated, cv);

    std::thread t1(&KeyboardReadTask::run, &kbTask);
    std::thread t2(&ServerReadTask::run, &serverTask);

    t1.join();
    t2.join();

    connectionHandler.close();
    //std::cout << "Exiting...\n" << std::endl;
    return 0;
}