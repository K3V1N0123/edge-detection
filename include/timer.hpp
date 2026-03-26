#pragma once

#include <chrono>

class Timer {
public:
    void start();
    double stopMillis();

private:
    std::chrono::steady_clock::time_point start_time_;
};
