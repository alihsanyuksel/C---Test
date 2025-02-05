#include <iostream>
#include <string>
#include <cstring>

void strcpyFunction(const char* input) {
    char buffer[256]; // Daha büyük bir arabellek kullanılıyor
    strcpy(buffer, input);
    std::cout << "Arabellek: " << buffer << std::endl;
}

std::string snprintfFunction(const std::string& input) {
    char buffer[256]; // Daha büyük bir arabellek kullanılıyor
    int result = snprintf(buffer, sizeof(buffer), "%s", input.c_str());
    if (result < 0 || result >= sizeof(buffer)) {
        std::cerr << "Arabellek boyutu yetersiz. Girilen metin: " << input << std::endl;
        return "";
    }
    return std::string(buffer);
}

int main() {
    std::string userInput;
    std::cout << "Metin girin: ";
    std::getline(std::cin, userInput);

    strcpyFunction(userInput.c_str());

    std::string result = snprintfFunction(userInput);
    std::cout << "snprintf sonucu: " << result << std::endl;

    return 0;
}