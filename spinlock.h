#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <atomic>
#include <vector>
#include <thread>
#include <iostream>

class Spinlock {
    public:
        Spinlock();
        int lock(int &spinTime);
        void unlock();

    private:
        std::atomic_flag flag;
};

#endif