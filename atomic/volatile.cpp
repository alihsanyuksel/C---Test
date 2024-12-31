#include <iostream>
#include <thread>
#include <vector>

volatile int counter = 0; // Shared counter

void incrementCounter() {
    for (int i = 0; i < 100000; ++i) {
        counter++; // Data race!
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.push_back(std::thread(incrementCounter));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}