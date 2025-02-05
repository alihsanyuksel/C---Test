#include <iostream>
#include <string>
#include <cstring>
#include <algorithm> // for std::min

void safeFunction(const char* input) {
    const size_t bufferSize = 16;
    char buffer[bufferSize];

    // Use strncpy to prevent buffer overflows
    strncpy(buffer, input, bufferSize - 1); // Copy at most bufferSize - 1 characters
    buffer[bufferSize - 1] = '\0'; // Ensure null termination

    std::cout << "Buffer contents: " << buffer << std::endl;
}

std::string safeStringFunction(const std::string& input) {
    const size_t bufferSize = 16;
    char buffer[bufferSize];

    // Use snprintf correctly, including space for null terminator
    int result = snprintf(buffer, bufferSize, "%s", input.c_str());

    if (result < 0) {
        throw std::runtime_error("snprintf encoding error");
    } else if (static_cast<size_t>(result) >= bufferSize) {
        // Handle truncation, if needed. For example, throw an error or log a warning.
        std::cerr << "Input string was truncated." << std::endl;
        return std::string(buffer, bufferSize - 1); // Return truncated string
    }

    return std::string(buffer);
}

int main() {
    std::string userInput;

    std::cout << "Enter some text: ";
    std::getline(std::cin, userInput);

    // Safe function call
    safeFunction(userInput.c_str());

    //Safe String function call
    try {
        std::string result = safeStringFunction(userInput);
        std::cout << "Result of safe string function: " << result << std::endl;
    } catch (const std::runtime_error& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}