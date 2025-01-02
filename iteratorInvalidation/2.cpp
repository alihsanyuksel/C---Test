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

std::vector<User>::iterator index_erase = users.begin();
while(index_erase != users.end()){
  if (!index_erase->isActive) {
    std::cout << "Aktif olmayan kullanıcı kaldırılıyor: " << index_erase->name <<std::endl;
    index_erase = users.erase(index_erase);
  }
  else{
    index_erase++;
  }
}

std::cout << "\nAktif kullanıcılar: " << std::endl;
for (const auto& user :users) {
  std::cout << user.name << std::endl;
}

return 0;
}