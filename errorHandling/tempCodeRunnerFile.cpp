#include <iostream>
#include <future>
#include <stdexcept>
#include <chrono>
#include <random>
#include <thread>
#include <vector>
#include <list>

// Fonksiyon, geleceği ve ID'si verilmiş işlemleri bir try-catch çerçevesinde işler
void processFuture(std::future<int>& future, int id, std::list<std::string>& errorLog) {
    try {
        int result = future.get();
        std::cout << "Result for ID " << id << ": " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error with future for ID " << id << ": " << e.what() << std::endl;
        errorLog.push_back(e.what());
    }
}

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
    std::list<std::string> errorLog; // Hataları kaydedeceğimiz bir liste

    // Gelecekleri bir vektörde tut
    std::vector<std::future<int>> futures;
    for (int i = 1; i <= 3; ++i) {
        futures.push_back(std::async(std::launch::async, potentiallyFailingOperation, i));
    }

    // Geçmişleri işle
    for (size_t i = 0; i < futures.size(); ++i) {
        processFuture(futures[i], i + 1, errorLog);
    }

    // Toplu hata raporu
    if (!errorLog.empty()) {
        std::cerr << "Summary of errors:" << std::endl;
        for (const auto& error : errorLog) {
            std::cerr << error << std::endl;
        }
    }
    
    std::cout << "Program continues..." << std::endl;
    return 0;
}