#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* data;
    int size;      // Number of elements currently stored
    int capacity;  // Maximum number of elements that can be stored

    void resize(int newCapacity);

public:
    DynamicArray();
    DynamicArray(int initialCapacity);
    ~DynamicArray();

    int getSize() const;
    int getCapacity() const;
    bool isEmpty() const;

    void push_back(const T& value);
    T& at(int index);
    const T& at(int index) const; // Const version
    void insert(int index, const T& value);
    void erase(int index);
};

#include "DynamicArray.cpp" // Include the implementation

#endif