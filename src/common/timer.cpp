#include "timer.hpp"

void Timer::start() {
    start_time_ = std::chrono::steady_clock::now();
}

double Timer::stopMillis() {
    const auto end_time = std::chrono::steady_clock::now();
    const auto duration = end_time - start_time_;
    return std::chrono::duration<double, std::milli>(duration).count();
}
