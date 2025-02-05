#include <iostream>
#include <vector>
#include <string>

struct Item {
    std::string ad;
    int miktar;
    double fiyat;
};

int main() {
    std::vector<Item*> envanter;

    envanter.push_back(new Item{"atlet", 10, 20.0});
    envanter.push_back(new Item{"pantolon", 5, 30.0});
    envanter.push_back(new Item{"ayakkabi", 3, 50.0});

    double toplam = 0;

    for (size_t i = 0; i < envanter.size(); ++i) {
        if (envanter[i]->miktar > 0) {
            toplam += envanter[i]->miktar * envanter[i]->fiyat;
        }
    }

    std::vector<Item*> silinecekler;

    for (size_t i = 0; i < envanter.size(); ++i) {
        if (envanter[i]->ad == "ayakkabi") {
            silinecekler.push_back(envanter[i]);
        }
    }

    for (size_t i = 0; i < silinecekler.size(); ++i) {
        delete silinecekler[i];
        envanter.erase(std::remove(envanter.begin(), envanter.end(), silinecekler[i]), envanter.end());
    }

    std::cout << "Toplam: " << toplam << std::endl;

    for (size_t i = 0; i < envanter.size(); ++i) {
        std::cout << envanter[i]->ad << std::endl;
    }

    for (size_t i = 0; i < envanter.size(); ++i) {
        delete envanter[i];
    }

    envanter.clear();

    return 0;
}