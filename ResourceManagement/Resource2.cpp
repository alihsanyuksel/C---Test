#include <iostream>
#include <fstream> // For std::fstream
#include <stdexcept>

// RAII approach using std::ofstream
void processFileWithRAII(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file.");
    }
    
    // Simulate some operation that might throw an exception
    try {
        // ... some code that might throw an exception ...
        throw std::runtime_error("Simulated exception during file processing.");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw; // Rethrow the exception.
    }

    // No need to explicitly close the file; it will be closed automatically when 'file' goes out of scope.
}

int main() {
    try {
        processFileWithRAII("test.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Main caught an error: " << e.what() << std::endl;
    }
    return 0;
}