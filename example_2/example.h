#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

typedef void (*Callback)();


class Timer {
public:
    Timer();
    ~Timer();
    // void start(int duration, Callback callback);
    void Timer::start(int duration, int (*cb)());
    void stop();
private:
    std::thread timerThread;
    bool running = false;
};


#endif