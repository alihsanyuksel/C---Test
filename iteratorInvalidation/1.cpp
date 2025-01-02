#include <iostream>
#include <vector>
#include <string>

struct User {
  std::string name;
  bool isActive;
  int data[1000];
  
  User(const std::string& n, bool active) : name(n), isActive(active){}
};

int main() {
  std::vector<User> users = {
    {"Ali", true},
    {"Veli", false},
    {"Ece", true},
    {"Selim", false},
    {"Elif", true},
    {"Sarp", false},
    {"Efe", true},
    {"Emir", false},
  };

  // Aktif olmayan kullanıcıları geriye doğru silmek için reverse_iterator kullanıyoruz
  for (auto it = users.rbegin(); it != users.rend(); it++) {
    if (!it->isActive) {
      std::cout << "Aktif olmayan kullanıcı kaldırılıyor: " << it->name << std::endl;
      users.erase(it);
    }
  }

  std::cout << "\nAktif kullanıcılar: " << std::endl;
  for (const auto& user : users) {
    std::cout << user.name << std::endl;
  }

  return 0;
}