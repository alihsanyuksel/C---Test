#include <iostream>
#include <memory>  // Akıllı işaretçiler için gerekli

struct MyClass {
    int value;
    MyClass(int v) : value(v) { std::cout << "MyClass constructed with " << value << std::endl; }
    ~MyClass() { std::cout << "MyClass destroyed with " << value << std::endl; }
};

void processData(const std::unique_ptr<MyClass>& obj) {
    if (obj) {
        std::cout << "Processing data: " << obj->value << std::endl;
        if (obj->value < 0)
            throw std::runtime_error("Negative value");
    }
}

int main() {
    std::unique_ptr<MyClass> obj1 = std::make_unique<MyClass>(10);
    processData(obj1);

    try {
        std::unique_ptr<MyClass> obj2 = std::make_unique<MyClass>(-5);
        processData(obj2);
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }
    // `obj2` otomatik olarak serbest bırakılır.

    std::unique_ptr<MyClass> obj3 = std::make_unique<MyClass>(20);
    MyClass *danglingPointer = obj3.get();
    obj3.reset();  // Belleği serbest bırakır.
    // std::cout << "Accessing dangling pointer: " << danglingPointer->value << std::endl;  // Yapılmamalı, çünkü belleğe artık erişilemez.

    return 0;
}