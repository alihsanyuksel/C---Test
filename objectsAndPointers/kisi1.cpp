#include <iostream>
#include <string>
#include <memory>

struct Address {
  std::string street;
  std::string city;
  
  Address(const std::string& s, const std::string& c) : street(s), city(c) {}

  void printAddress() const {
    std::cout << "Street: " << street << ", City: " << city << std::endl;
  }

  // Non-const version of getStreet
  std::string& getStreet() {
    return street;
  }

  // Const version of getStreet
  const std::string& getStreet() const {
    return street;
  }
};

struct Person {
  std::string name;
  int age;
  std::unique_ptr<Address> address; // Use smart pointer here
  
  Person(const std::string& n, int a, const std::string& s, const std::string& c)
    : name(n), age(a), address(std::make_unique<Address>(s, c)) {}

  void printPersonDetails() const {
    std::cout << "Name: " << name << ", Age: " << age << std::endl;
    if (address) {
      address->printAddress();
    }
  }

  const Address* getAddress() const {
    return address.get();
  }
};

int main() {
  Person person1("Ali", 30, "123 Ana Cad", "Ankara");
  person1.printPersonDetails();

  const Person person2("Veli", 25, "789 Cad", "Bursa");
  person2.printPersonDetails();
  
 
  const Person* const person3 = new Person("Elif", 40, "20 Cad", "Antalya");
  person3->printPersonDetails();
  
  // Uncommenting the below line will cause a compile error, as desired
  // person3->getAddress()->getStreet() = "New Street";

  delete person3; // Remember to delete dynamically allocated memory
  return 0;
}