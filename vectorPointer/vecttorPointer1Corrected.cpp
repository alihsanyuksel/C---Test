#include <iostream>
#include <vector>
#include <string>
#include <memory> // For std::unique_ptr
#include <algorithm> // For std::remove_if

struct Item {
    std::string ad;
    int miktar;
    double fiyat;
};

// Function to check if an item should be removed
bool itemSilme(const std::unique_ptr<Item>& item) {
    return item->ad == "ayakkabi";
}

// Calculate total value of the inventory
double toplamDegeriHesapla(const std::vector<std::unique_ptr<Item>>& envanter) {
    double toplam = 0;
    for (const auto& item : envanter) {
        if (item->miktar > 0) {
            toplam += item->miktar * item->fiyat;
        }
    }
    return toplam;
}

int main() {
    std::vector<std::unique_ptr<Item>> envanter;
    
    // Correctly initialize items using std::make_unique
    envanter.push_back(std::make_unique<Item>(Item{"atlet", 10, 20.0}));
    envanter.push_back(std::make_unique<Item>(Item{"pantolon", 5, 30.0}));
    envanter.push_back(std::make_unique<Item>(Item{"ayakkabi", 3, 50.0}));

    // Calculate the total value
    double toplam = toplamDegeriHesapla(envanter);
    std::cout << "Toplam: " << toplam << std::endl;

    // Remove items with the name "ayakkabi"
    envanter.erase(
        std::remove_if(envanter.begin(), envanter.end(), itemSilme),
        envanter.end()
    );

    // Print remaining items in the inventory
    for (const auto& item : envanter) {
        std::cout << item->ad << std::endl;
    }

    return 0;
}
