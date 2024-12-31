#include <iostream>
#include <future>
#include <stdexcept>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

// Potansiyel olarak başarısız olan işlem
int potentiallyFailingOperation(int id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);
    int randomValue = distrib(gen);

    if (randomValue <= 3) {
        throw std::runtime_error("Operation failed for ID: " + std::to_string(id));
    }

    if (randomValue > 7) { // 30% chance to simulate a long operation
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Long operation finished for ID: " << id << std::endl;
    }
    
    return id * 10;
}

// Future'ları bir diziye alarak tek bir try-catch blokunda işleme alınır.
void processFutures(std::vector<std::future<int>>& futures) {
    for (size_t i = 0; i < futures.size(); ++i) {
        try {
            int result = futures[i].get();
            std::cout << "Result " << (i + 1) << ": " << result << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "Error with future " << (i + 1) << ": " << e.what() << std::endl;
        }
    }
}

int main() {
    std::vector<std::future<int>> futures;
    futures.emplace_back(std::async(std::launch::async, potentiallyFailingOperation, 1));
    futures.emplace_back(std::async(std::launch::async, potentiallyFailingOperation, 2));
    futures.emplace_back(std::async(std::launch::async, potentiallyFailingOperation, 3));

    processFutures(futures);

    std::cout << "Program continues..." << std::endl;
    return 0;
}