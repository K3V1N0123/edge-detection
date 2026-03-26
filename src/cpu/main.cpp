#include <iostream>

#include "timer.hpp"

int main() {
    std::cout << "CPU baseline scaffold ready" << std::endl;

    Timer timer;
    timer.start();

    volatile int placeholder = 0;
    for (int i = 0; i < 100000; ++i) {
        placeholder += i;
    }

    std::cout << "Placeholder elapsed time: " << timer.stopMillis() << " ms" << std::endl;
    return placeholder == -1 ? 1 : 0;
}
