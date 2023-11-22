#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "list.h"

void insertWithGlobalLock(List& list, int value) { list.insert(value); }

void insertWithFineGrainedLock(List& list, int value) {
  list.insertFineGrained(value);
}

int main() {
  List myList;
  std::vector<long long> timingsGlobal, timingsFineGrained;
  std::vector<int> initial_values = {40, 50, 100, 120, 160, 180};

  // 1. Insert initial values using global lock
  for (int val : initial_values) {
    myList.insert(val);
  }

  // Insert values with global lock and measure time
  for (int i = 0; i < 5; ++i) {
    auto start = std::chrono::high_resolution_clock::now();

    // Perform insertion with global lock
    std::thread t1(insertWithGlobalLock, std::ref(myList), 65);
    std::thread t2(insertWithGlobalLock, std::ref(myList), 77);

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();

    timingsGlobal.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count());
  }

  // Insert values with fine-grained lock and measure time
  for (int i = 0; i < 5; ++i) {
    auto start = std::chrono::high_resolution_clock::now();

    // Perform insertion with fine-grained lock
    std::thread t1(insertWithFineGrainedLock, std::ref(myList), 65);
    std::thread t2(insertWithFineGrainedLock, std::ref(myList), 77);

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();

    timingsFineGrained.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count());
  }

  // Calculate and print average timings
  long long sumGlobal = 0, sumFineGrained = 0;
  for (auto t : timingsGlobal) sumGlobal += t;
  for (auto t : timingsFineGrained) sumFineGrained += t;

  std::cout << "Average time with global lock: "
            << (sumGlobal / timingsGlobal.size()) << " microseconds\n";
  std::cout << "Average time with fine-grained lock: "
            << (sumFineGrained / timingsFineGrained.size())
            << " microseconds\n";

  // 4. Comparison of processes
  // This would be a discussion rather than code.
  // Discuss the benefits of global vs fine-grained locking in terms of
  // simplicity, overhead, contention, etc.

  // Print the list
  myList.printList();

  return 0;
}
