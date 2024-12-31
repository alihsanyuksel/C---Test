#include <iostream>
#include <fstream>
#include <stdexcept>

void processFileRAII(const char* filename) {
    std::ofstream file(filename); // RAII: File is opened in the constructor

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file.");
    }

    try {
        // ... some code that might throw an exception ...
        file << "Some data to the file" << std::endl;
        throw std::runtime_error("Simulated exception during file processing.");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }

} // RAII: File is automatically closed in the destructor, even if exceptions are thrown

int main() {
    try {
        processFileRAII("test_raii.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Main caught an error: " << e.what() << std::endl;
    }
    return 0;
}