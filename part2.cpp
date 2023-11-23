#include <vector>
#include <thread>
#include "spinlock.h"

const int NUM_THREADS = 5;

void Task(Spinlock& lock, int& spinCount, int& spinTime, int& totalTime) {
    auto startTime = std::chrono::high_resolution_clock::now();

    spinCount = lock.lock(spinTime);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    lock.unlock();

    auto endTime = std::chrono::high_resolution_clock::now();

    totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}


int main() {
    std::vector<std::thread> threads;
    Spinlock spinlock;
    std::vector<int> counts(NUM_THREADS, 0);
    std::vector<int> totalTimes(NUM_THREADS, 0);
    std::vector<int> spinTimes(NUM_THREADS, 0);

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(Task, std::ref(spinlock), std::ref(counts[i]), std::ref(spinTimes[i]), std::ref(totalTimes[i]));
    }

    for (auto& t : threads) {
        t.join();
    }

    // Output the recorded times for each thread
    for (int i = 0; i < NUM_THREADS; ++i) {
        std::cout << "Thread " << i + 1 << ": Spinning count = " << counts[i] 
                  << " cycles, Spin time = " << spinTimes[i] << "ms and Total time = " << totalTimes[i] << "ms\n";
    }

    return 0;
}
