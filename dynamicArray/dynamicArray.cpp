#include "DynamicArray.h"
#include <algorithm> // for std::copy

template <typename T>
void DynamicArray<T>::resize(int newCapacity) {
    if (newCapacity < size) {
        throw std::runtime_error("New capacity is less than current size");
    }

    T* newData = new T[newCapacity];
    std::copy(data, data + size, newData); // Copy existing data

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(0) {}

template <typename T>
DynamicArray<T>::DynamicArray(int initialCapacity) : size(0), capacity(initialCapacity) {
    if (initialCapacity < 0) {
        throw std::runtime_error("Initial capacity cannot be negative");
    }
    data = (capacity > 0) ? new T[capacity] : nullptr;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

template <typename T>
int DynamicArray<T>::getCapacity() const {
    return capacity;
}

template <typename T>
bool DynamicArray<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }
    data[size++] = value;
}

template <typename T>
T& DynamicArray<T>::at(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index is out of range");
    }
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::at(int index) const{
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index is out of range");
    }
    return data[index];
}

template <typename T>
void DynamicArray<T>::insert(int index, const T& value){
    if (index < 0 || index > size) {
        throw std::out_of_range("Index is out of range");
    }
    if(size == capacity){
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }
    for(int i = size; i > index; --i){
        data[i] = data[i-1];
    }
    data[index] = value;
    size++;
}

template <typename T>
void DynamicArray<T>::erase(int index){
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index is out of range");
    }
    for(int i = index; i < size-1; ++i){
        data[i] = data[i+1];
    }
    size--;
}