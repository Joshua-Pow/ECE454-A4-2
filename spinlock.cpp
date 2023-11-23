#include <atomic>
#include <vector>
#include <thread>
#include <iostream>
#include "spinlock.h"

Spinlock::Spinlock() : flag(ATOMIC_FLAG_INIT) {}

int Spinlock::lock(int &spinTime) {
    int counter = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    while (flag.test_and_set(std::memory_order_acquire)) {
        ++counter;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    spinTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    return counter;
}

void Spinlock::unlock() {
    flag.clear(std::memory_order_release);
}