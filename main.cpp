#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

// Fonksiyon prototipleri
int calculateGCD(int a, int b);
int calculateLCM(int a, int b);
bool isInteger(const std::string& str);

int main() {
    std::string inputGCD, inputLCM;
    
    std::cout << "EBOB'u girin: ";
    std::cin >> inputGCD;
    if (!isInteger(inputGCD)) {
        std::cerr << "Hata: EBOB tam sayı olmalı!" << std::endl;
        return 1;
    }

    std::cout << "EKOK'u girin: ";
    std::cin >> inputLCM;
    if (!isInteger(inputLCM)) {
        std::cerr << "Hata: EKOK tam sayı olmalı!" << std::endl;
        return 1;
    }

    int gcd = std::stoi(inputGCD);
    int lcm = std::stoi(inputLCM);

    // Giriş doğrulaması
    if (lcm % gcd != 0) {
        std::cerr << "Hata: EKOK, EBOB'un bir katı olmalı!" << std::endl;
        return 1;
    }

    int product = gcd * lcm;
    std::vector<std::pair<int, int>> validPairs;

    // Tüm olası (a, b) çiftlerini hesapla
    for (int a = gcd; a <= sqrt(product); a += gcd) {
        if (product % a == 0) {
            int b = product / a;
            if (calculateGCD(a, b) == gcd && calculateLCM(a, b) == lcm) {
                validPairs.emplace_back(a, b);
            }
        }
    }

    if (validPairs.empty()) {
        std::cout << "Hiçbir geçerli çift bulunamadı." << std::endl;
    } else {
        std::cout << "Geçerli (a, b) çiftleri:" << std::endl;
        for (const auto& pair : validPairs) {
            std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
        }
    }

    return 0;
}

// EBOB hesaplama fonksiyonu
int calculateGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// EKOK hesaplama fonksiyonu
int calculateLCM(int a, int b) {
    return (a / calculateGCD(a, b)) * b;
}

// Tam sayı kontrol fonksiyonu
bool isInteger(const std::string& str) {
    if (str.empty() || (str[0] != '-' && !isdigit(str[0]))) {
        return false;
    }
    for (size_t i = 1; i < str.size(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
