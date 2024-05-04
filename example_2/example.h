// Timer.h
#pragma once
#include <chrono>

class Timer {
public:
    Timer() : start_time(std::chrono::high_resolution_clock::now()) {}

    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    double elapsed() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return duration.count() * 0.001; // Convert microseconds to milliseconds
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};
