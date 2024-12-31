#include <iostream>
#include <cstdio> // For fopen, fclose
#include <stdexcept>

void processFileManually(const char* filename) {
    FILE* file = std::fopen(filename, "w");
    if (file == nullptr) {
        throw std::runtime_error("Failed to open file.");
    }

    // Simulate some operation that might throw an exception
    try {
        // ... some code that might throw an exception ...
        throw std::runtime_error("Simulated exception during file processing.");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        //Problem is if we only handle the error here, the file will remain open.
        //std::fclose(file); // if we put it here it will be ok but hard to maintain
        //rethrowing is also possible.
        throw; //rethrow the exception.
    }
    // if there is no try catch block and exception is thrown, this code will not be executed.
    std::fclose(file); // If an exception is thrown before this line, the file is not closed!
}

int main() {
    try {
        processFileManually("test.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Main caught an error: " << e.what() << std::endl;
    }
    return 0;
}