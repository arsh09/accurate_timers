#include "example.h"

Timer::Timer() : running(false) {}

Timer::~Timer() {
    stop();
}

void Timer::start(int duration, int (*cb)()) {
    if (running) {
        stop();
    }
    running = true;
    timerThread = std::thread([this, duration, cb]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        if (running && cb) cb();
        running = false;
    });
    timerThread.detach();
}

void Timer::stop() {
    running = false;
    if (timerThread.joinable()) {
        timerThread.join();
    }
}