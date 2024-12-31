#include <iostream>
#include <string>

struct Address {
    std::string street;
    std::string city;

    Address(const std::string& s, const std::string& c) : street(s), city(c) {}

    void printAddress() const {
        std::cout << "Street: " << street << ", City: " << city << std::endl;
    }

    std::string& getStreet() { // Non-const reference return
        return street;
    }
};

struct Person {
    std::string name;
    int age;
    Address* address;

    Person(const std::string& n, int a, const std::string& s, const std::string& c)
        : name(n), age(a), address(new Address(s, c)) {}

    ~Person() { delete address; }

    void printPersonDetails() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
        if (address) {
            address->printAddress();
        }
    }
    const Address* getAddress() const{
        return address;
    }
};

int main() {
    Person person1("Alice", 30, "123 Main St", "Anytown");
    person1.printPersonDetails();

    const Person person2("Bob", 25, "789 Oak Ave", "Springfield");
    person2.printPersonDetails(); // OK now
    //person2.getAddress()->getStreet() = "New Street"; // Modifies the street!


    const Person* const person3 = new Person("Charlie", 40, "10 High st", "London");
    person3->printPersonDetails(); // OK now
    //person3->getAddress()->getStreet() = "New Street"; //Error: assignment of read-only location ‘*(person3->Person::address)’
    delete person3;

    return 0;
}