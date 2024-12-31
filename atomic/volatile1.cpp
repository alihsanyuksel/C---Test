#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

std::atomic<int> counter(0); // Atomic counter

void incrementCounter() {
    for (int i = 0; i < 100000; ++i) {
        ++counter; // Atomic increment
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(incrementCounter);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final counter value: " << counter.load() << std::endl;
    return 0;
}