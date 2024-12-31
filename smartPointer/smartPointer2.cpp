#include <iostream>
#include <memory>

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
    // obj1 için unique_ptr kullanma 
    auto obj1 = std::make_unique<MyClass>(10);
    processData(obj1); // unique_ptr ile istisna güvenliği

    // obj2 istisna güvenliği
    try {
        auto obj2 = std::make_unique<MyClass>(-5);
        processData(obj2);
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }
    //obj2 otomatik olarak yok edildiğinden, bellek sızıntısı yok

    // Sallanan işaretçilerden tamamen kurtulma
    {
        auto obj3 = std::make_unique<MyClass>(20);
        processData(obj3);
        //  Reset ya da deletion işlemi yok, obj3 kapsam dışına çıkar ve yok edilir
    } // obj3 burada yok edilir

    std::cout << "Program completed safely without memory issues." << std::endl;

    return 0;
}
