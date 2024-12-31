#include <iostream>
#include <future>
#include <stdexcept>
#include <chrono>
#include <random>
#include <thread>
#include <vector>
#include <string>

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

template<typename T>
void handleFuture(std::future<T>& future, std::vector<std::string>& errors, int id) {
    try {
        T result = future.get();
        std::cout << "Result " << id << ": " << result << std::endl;
    } catch (const std::exception& e) { // Use std::exception for broader error handling
        std::string errorMessage = "Error with future " + std::to_string(id) + ": " + e.what();
        std::cerr << errorMessage << std::endl;
        errors.push_back(errorMessage);
    }
}

int main() {
    std::vector<std::future<int>> futures;
    std::vector<std::string> errors;

    // Add futures dynamically in a loop to avoid duplication
    for (int i = 1; i <= 3; ++i) {
        futures.emplace_back(std::async(std::launch::async, potentiallyFailingOperation, i));
    }

    for (size_t i = 0; i < futures.size(); ++i) {
        handleFuture(futures[i], errors, i + 1);
    }

    if (!errors.empty()) {
        std::cerr << "Summary of errors:" << std::endl;
        for (const auto& error : errors) {
            std::cerr << error << std::endl;
        }
    } else {
        std::cout << "All operations completed successfully." << std::endl;
    }

    std::cout << "Program continues..." << std::endl;
    return 0;
}
