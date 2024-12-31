#include <iostream>
#include <cassert>
#include "DynamicArray.h"

// Test functions declarations
void testConstructors();
void testGetSizeAndIsEmpty();
void testGetCapacity();
void testPushBack();
void testAt();
void testInsert();
void testErase();
void testMultipleDataTypes();

int main() {
    std::cout << "Starting DynamicArray tests..." << std::endl;

    testConstructors();
    testGetSizeAndIsEmpty();
    testGetCapacity();
    testPushBack();
    testAt();
    testInsert();
    testErase();
    testMultipleDataTypes();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}

// Test default and parameterized constructors
void testConstructors() {
    // Default constructor
    DynamicArray<int> defaultArray;
    assert(defaultArray.getSize() == 0);
    assert(defaultArray.isEmpty());
    std::cout << "Default constructor test passed." << std::endl;

    // Parameterized constructor with valid capacity
    DynamicArray<int> paramArray(5);
    assert(paramArray.getSize() == 0);
    assert(paramArray.getCapacity() == 5);
    std::cout << "Parameterized constructor test passed." << std::endl;

    // Parameterized constructor with negative capacity
    try {
        DynamicArray<int> invalidArray(-1);
        assert(false); // This should not be reached
    } catch (const std::runtime_error& e) {
        std::cout << "Exception for negative capacity test passed: " << e.what() << std::endl;
    }
}

// Test getSize() and isEmpty()
void testGetSizeAndIsEmpty() {
    DynamicArray<int> array;
    assert(array.getSize() == 0);
    assert(array.isEmpty());

    array.push_back(10);
    assert(array.getSize() == 1);
    assert(!array.isEmpty());

    array.erase(0);
    assert(array.getSize() == 0);
    assert(array.isEmpty());
    std::cout << "getSize() and isEmpty() tests passed." << std::endl;
}

// Test getCapacity()
void testGetCapacity() {
    DynamicArray<int> array(3);
    assert(array.getCapacity() == 3);

    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    array.push_back(4); // Triggers resize
    assert(array.getCapacity() > 3);
    std::cout << "getCapacity() test passed." << std::endl;
}

// Test push_back()
void testPushBack() {
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    assert(array.getSize() == 3);
    assert(array.at(0) == 1);
    assert(array.at(1) == 2);
    assert(array.at(2) == 3);
    std::cout << "push_back() test passed." << std::endl;
}

// Test at()
void testAt() {
    DynamicArray<int> array;
    array.push_back(5);
    array.push_back(10);

    assert(array.at(0) == 5);
    assert(array.at(1) == 10);

    try {
        array.at(-1);
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "at() negative index test passed: " << e.what() << std::endl;
    }

    try {
        array.at(2);
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "at() out-of-range index test passed: " << e.what() << std::endl;
    }
}

// Test insert()
void testInsert() {
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(3);

    array.insert(1, 2); // Insert 2 at index 1
    assert(array.getSize() == 3);
    assert(array.at(1) == 2);

    try {
        array.insert(-1, 4);
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "insert() negative index test passed: " << e.what() << std::endl;
    }

    try {
        array.insert(5, 4); // Invalid index
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "insert() out-of-range index test passed: " << e.what() << std::endl;
    }
    std::cout << "insert() test passed." << std::endl;
}

// Test erase()
void testErase() {
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    array.erase(1); // Remove element at index 1
    assert(array.getSize() == 2);
    assert(array.at(1) == 3);

    try {
        array.erase(-1);
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "erase() negative index test passed: " << e.what() << std::endl;
    }

    try {
        array.erase(5);
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "erase() out-of-range index test passed: " << e.what() << std::endl;
    }
    std::cout << "erase() test passed." << std::endl;
}

// Test with multiple data types
void testMultipleDataTypes() {
    // Test with int
    DynamicArray<int> intArray;
    intArray.push_back(42);
    assert(intArray.at(0) == 42);

    // Test with std::string
    DynamicArray<std::string> strArray;
    strArray.push_back("hello");
    assert(strArray.at(0) == "hello");

    std::cout << "Multiple data types test passed." << std::endl;
}
