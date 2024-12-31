#include <iostream>
#include <future>
#include <stdexcept>
#include <chrono>
#include <random>
#include <thread>

int potentiallyFailingOperation(int id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);
    int randomValue = distrib(gen);

    if (randomValue <= 3) {
        throw std::runtime_error("Operation failed for ID: " + std::to_string(id));
    }

    if (randomValue > 7){ // 30% chance to simulate a long operation
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Long operation finished for ID: " << id << std::endl;
    }
    
    return id * 10;
}

int main() {
    std::future<int> future1 = std::async(std::launch::async, potentiallyFailingOperation, 1);
    std::future<int> future2 = std::async(std::launch::async, potentiallyFailingOperation, 2);
    std::future<int> future3 = std::async(std::launch::async, potentiallyFailingOperation, 3);

    try {
        int result1 = future1.get();
        std::cout << "Result 1: " << result1 << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error with future1: " << e.what() << std::endl;
    }

    try {
        int result2 = future2.get();
        std::cout << "Result 2: " << result2 << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error with future2: " << e.what() << std::endl;
    }

    try {
        int result3 = future3.get();
        std::cout << "Result 3: " << result3 << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error with future3: " << e.what() << std::endl;
    }

    std::cout << "Program continues..." << std::endl;
    return 0;
}