#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <iostream>

class Timer {
public:
    Timer() : running(false) {}
    virtual ~Timer() {
        stopTimer();
    }

    void startTimer(int interval_ms) {
        if (running) return;  // Prevent multiple starts
        running = true;
        worker = std::thread([this, interval_ms]() {
            while (running) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
                if (running) {
                    float ms = interval_ms;
                    onTimeout(ms);
                }
            }
        });

        // worker.detach();
    }

    void stopTimer() {
        running = false;
        std::cout << "stopping the timer." << std::endl;
        if (worker.joinable()) {
            worker.join();  // Wait for the thread to finish
        }
    }

    // Virtual method to be overridden in JavaScript
    virtual void onTimeout(float ms) {
        // Default implementation (can be empty)
    }

private:
    std::thread worker;
    std::atomic<bool> running;
};

#endif // TIMER_H
