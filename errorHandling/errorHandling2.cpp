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

std::vector<std::string> handleFuture(std::future<int>& future) {
    try {
        int result = future.get();
        std::string message = "Result: " + std::to_string(result);
        return {message};
    } catch (const std::exception& e) {
        std::string message = std::string("Error: ") + e.what();
        return {message};
    }
}

int main() {
    std::vector<std::future<int>> futures;
    for (int i = 1; i <= 3; ++i) {
        futures.emplace_back(std::async(std::launch::async, potentiallyFailingOperation, i));
    }

    std::vector<std::string> results;
    for (auto& future : futures) {
        auto futureResults = handleFuture(future);
results.insert(results.end(), futureResults.begin(), futureResults.end());
    }

    // Tüm sonuçlar ve hatalar raporlanır
    for (const auto& result : results) {
        std::cout << result << std::endl;
    }

    std::cout << "Program continues..." << std::endl;
    return 0;
}