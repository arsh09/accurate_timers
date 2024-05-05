#include "example.h"

Timer::Timer() : running(false) {}

Timer::~Timer() {
    stop();
}

void Timer::start(int duration, Callback callback) {
    if (running) {
        stop();
    }
    running = true;
    timerThread = std::thread([this, duration, callback]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        if (running && callback) callback();
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