#include <iostream>
#include <string>
#include <cstring> // For strcpy

void vulnerableFunction(const char* input) {
    char buffer[16]; // Fixed-size buffer
    strcpy(buffer, input); // Bug: strcpy is inherently unsafe, no bounds checking
    std::cout << "Buffer contents: " << buffer << std::endl;
}

std::string vulnerableStringFunction(const std::string& input) {
    char buffer[16];
    //Bug: Using snprintf with wrong size parameter
    snprintf(buffer, input.length(), "%s", input.c_str());
    return std::string(buffer);
}

int main() {
    std::string userInput;

    std::cout << "Enter some text: ";
    std::getline(std::cin, userInput);

    // First vulnerability
    try {
        vulnerableFunction(userInput.c_str());
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    //Second vulnerability
    try{
        std::string result = vulnerableStringFunction(userInput);
        std::cout << "Result of vulnerable function: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }


    return 0;
}