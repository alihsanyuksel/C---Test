#include <iostream>
#include <string>
#include <cstring>

void strcpyFunction(const char* input) {
  // Girdi uzunluğuna göre arabellek boyutunu belirle
  char buffer[strlen(input) + 1];
  strcpy(buffer, input);
  std::cout << "Arabellek : " << buffer << std::endl;
}

std::string snprintfFunction(const std::string& input) {
  // Girdi uzunluğuna göre arabellek boyutunu belirle
  char buffer[input.length() + 1];
  int result = snprintf(buffer, sizeof(buffer), "%s", input.c_str());
  // snprintf dönüş değeri, buffer boyutuna eşit mi?
  if (result == input.length()) {
    return std::string(buffer);
  } else {
    // Buffer yeterli değilse, hata mesajı yaz ve boş bir dize döndür
    std::cerr << "Buffer boyutu yeterli değil." << std::endl;
    return "";
  }
}

int main() {
  std::string userInput;
  std::cout << "Metin girin: ";
  std::getline(std::cin, userInput);

  try {
    strcpyFunction(userInput.c_str());
  } catch (const std::exception& e) {
    std::cerr << "Exception caught: " << e.what() << std::endl;
  }

  try {
    std::string result = snprintfFunction(userInput);
    std::cout << "snprintf sonucu: " << result << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Exception Caught: " << e.what() << std::endl;
  }

  return 0;
}