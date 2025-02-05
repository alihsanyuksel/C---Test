#include <iostream>
#include <vector>
#include <string>
#include <memory> // std::unique_ptr için
#include <algorithm> // remove_if için

struct Item {
  std::string ad;
  int miktar;
  double fiyat;
};

bool itemSilme(const Item& item) {
  return item.ad == "ayakkabi";
}

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
  
  envanter.push_back(std::make_unique<Item>("atlet", 10, 20.0));
  envanter.push_back(std::make_unique<Item>("pantolon", 5, 30.0));
  envanter.push_back(std::make_unique<Item>("ayakkabi", 3, 50.0));

  double toplam = toplamDegeriHesapla(envanter);
  std::cout << "Toplam: " << toplam << std::endl;

  // Öğeleri adlarına göre silme
  envanter.erase(
    std::remove_if(envanter.begin(), envanter.end(), itemSilme),
    envanter.end()
  );

  // Kalan öğeleri yazdırma
  for (const auto& item : envanter) {
    std::cout << item->ad << std::endl;
  }
  
  return 0;
}