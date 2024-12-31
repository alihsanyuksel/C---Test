#include <iostream>
#include <memory>

struct MyClass {
    int value;
    MyClass(int v) : value(v) { std::cout << "MyClass constructed with " << value << std::endl; }
    ~MyClass() { std::cout << "MyClass destroyed with " << value << std::endl; }
};

void processData(const std::unique_ptr<MyClass>& obj) { // Take a const reference to a unique_ptr
    if (obj) {
        std::cout << "Processing data: " << obj->value << std::endl;
        if (obj->value < 0) {
            throw std::runtime_error("Negative value");
        }
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
    } // obj2 is automatically destroyed here, no memory leak

    std::shared_ptr<MyClass> obj3 = std::make_shared<MyClass>(20);
    std::shared_ptr<MyClass> anotherShared = obj3; // Share ownership
    std::weak_ptr<MyClass> weakObj = obj3;

    if(auto sharedObj = weakObj.lock()){
        std::cout << "Weak ptr value: " << sharedObj->value << std::endl;
    }

    obj3.reset(); // obj3 is now nullptr, but anotherShared still points to the object
    if(auto sharedObj = weakObj.lock()){
        std::cout << "Weak ptr value: " << sharedObj->value << std::endl;
    } else {
        std::cout << "Object deleted" << std::endl;
    }
    anotherShared.reset(); // Object is now deleted as no shared pointers point to it.

    return 0;
}