#include <iostream>

struct MyClass {
    int value;
    MyClass(int v) : value(v) { std::cout << "MyClass constructed with " << value << std::endl; }
    ~MyClass() { std::cout << "MyClass destroyed with " << value << std::endl; }
};

void processData(MyClass* obj) {
    if (obj) {
        std::cout << "Processing data: " << obj->value << std::endl;
        //Bazı işlemler için error fırlatma simülasyonu
        if (obj->value < 0)
            throw std::runtime_error("Negative value");
    }
}

int main() {
    MyClass* obj1 = new MyClass(10);
    processData(obj1);
    delete obj1;

    MyClass* obj2 = new MyClass(-5);
    try {
        processData(obj2);
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }
    //istisna fırlatıılırsa bellek sızıntısı

    MyClass* obj3 = new MyClass(20);
    MyClass* danglingPointer = obj3;
    delete obj3;
    std::cout << "Accessing dangling pointer: " << danglingPointer->value << std::endl; // Öngörülemeyen Davranış

    return 0;
}