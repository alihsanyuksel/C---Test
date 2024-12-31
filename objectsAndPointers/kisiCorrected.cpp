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

    const std::string& getStreet() const { // Now returns a const reference
        return street;
    }
    void changeStreet(const std::string& newStreet) {
        street = newStreet;
    }
};

struct Person {
    std::string name;
    int age;
    std::unique_ptr<Address> address;

    Person(const std::string& n, int a, const std::string& s, const std::string& c)
        : name(n), age(a), address(std::make_unique<Address>(s, c)) {}

    ~Person() = default;

    void printPersonDetails() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
        if (address) {
            address->printAddress();
        }
    }
    const Address* getAddress() const{
        return address.get();
    }
    void changePersonAddressStreet(const std::string& newStreet){
        if(address){
            address->changeStreet(newStreet);
        }
    }
};

int main() {
    Person person1("Alice", 30, "123 Main St", "Anytown");
    person1.printPersonDetails();

    const Person person2("Bob", 25, "789 Oak Ave", "Springfield");
    person2.printPersonDetails();

    const auto person3 = std::make_unique<Person>("Charlie", 40, "10 High st", "London");
    person3->printPersonDetails();
    //person3->getAddress()->getStreet() = "New Street"; //Now error is correct: assignment of read-only location ‘*(person3->Person::address)’

    return 0;
}