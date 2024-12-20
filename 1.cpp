#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <sstream>

// Fonksiyon prototipleri
int calculateGCD(int a, int b);
int calculateLCM(int a, int b);

int main() {
    std::string inputGCD, inputLCM;
    int gcd, lcm;
    
    std::cout << "EBOB'u girin: ";
    if (!(std::cin >> inputGCD) || !(std::cin.ignore())) {
        std::cerr << "Hata: Geçerli bir girış yapmalısınız. Lütfen programı yeniden başlatınız." << std::endl;
        return 1;
    }

    std::cout << "EKOK'u girin: ";
    if (!(std::cin >> inputLCM) || !(std::cin.ignore())) {
        std::cerr << "Hata: Geçerli bir girış yapmalısınız. Lütfen programı yeniden başlatınız." << std::endl;
        return 1;
    }

    try {
        gcd = std::stoi(inputGCD);
        lcm = std::stoi(inputLCM);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Hata: EBOB veya EKOK tam sayı olmalı!" << std::endl;
        return 1;
    }

    // Giriş doğrulaması
    if (lcm % gcd != 0) {
        std::cerr << "Hata: EKOK, EBOB'un bir katı olmalı!" << std::endl;
        return 1;
    }

    int product = gcd * lcm;

    std::cout << "Geçerli (a, b) çiftleri bulunuyor..." << std::endl;

    // Tüm olası (a, b) çiftlerini hesapla
    // Bu döngü, EBOB'dan büyük ve EKOK'tan küçük olan tüm tam sayıları döndürür.
    for (int a = gcd; a <= product / gcd; ++a) {
        int b = product / a;
        if (calculateGCD(a, b) == gcd && calculateLCM(a, b) == lcm) {
            std::cout << "(" << a << ", " << b << ")" << std::endl;
        }
    }

    std::cout << "Geçerli (a, b) çiftleri bulundu." << std::endl;

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