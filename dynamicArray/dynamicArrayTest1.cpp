#include <iostream>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include "DynamicArray.h" // DynamicArray sınıfını tanımlayan dosyanı dahil edin

// Test fonksiyonları
void testConstructors();
void testGetSizeAndIsEmpty();
void testGetCapacity();
void testPushBack();
void testAt();
void testInsert();
void testErase();
void testWithDifferentTypes();

int main() {
    std::cerr << "DynamicArray Birim Testleri Başlatıldı..." << std::endl;
    testConstructors();
    testGetSizeAndIsEmpty();
    testGetCapacity();
    testPushBack();
    testAt();
    testInsert();
    testErase();
    testWithDifferentTypes();
    std::cerr << "DynamicArray Birim Testleri Tamamlandı." << std::endl;
    return 0;
}

// Yapılandırıcıları test eden fonksiyon
void testConstructors() {
    try {
        DynamicArray<int> array;
        assert(array.getSize() == 0 && array.getCapacity() == 0);

        DynamicArray<int> array2(5);
        assert(array2.getSize() == 0 && array2.getCapacity() == 5);

        std::cerr << "Yapılandırıcılar Testi Başarılı." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Yapılandırıcılar Testi Hatası: " << e.what() << std::endl;
    }
}

// getSize() ve isEmpty() methodlarını test eden fonksiyon
void testGetSizeAndIsEmpty() {
    DynamicArray<int> array;
    assert(array.getSize() == 0 && array.isEmpty());

    DynamicArray<int> array2(5);
    assert(array2.getSize() == 0 && array2.isEmpty());

    array.push_back(1);
    assert(array.getSize() == 1 && !array.isEmpty());

    array.erase(0);
    assert(array.getSize() == 0 && array.isEmpty());

    std::cerr << "getSize() ve isEmpty() Testi Başarılı." << std::endl;
}

// getCapacity() methodunu test eden fonksiyon
void testGetCapacity() {
    DynamicArray<int> array;
    assert(array.getCapacity() == 0);

    DynamicArray<int> array2(5);
    assert(array2.getCapacity() == 5);

    array2.push_back(1);
    assert(array2.getCapacity() == 5);

    array2.push_back(2);
    assert(array2.getCapacity() == 5);

    array2.push_back(3);
    array2.push_back(4);
    array2.push_back(5);
    array2.push_back(6);
    assert(array2.getCapacity() == 10);

    std::cerr << "getCapacity() Testi Başarılı." << std::endl;
}

// push_back() methodunu test eden fonksiyon
void testPushBack() {
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    assert(array.at(0) == 1 && array.at(1) == 2 && array.at(2) == 3);

    array.push_back(4);
    array.push_back(5);
    array.push_back(6);
    assert(array.at(3) == 4 && array.at(4) == 5 && array.at(5) == 6);

    std::cerr << "push_back() Testi Başarılı." << std::endl;
}

// at() methodunu test eden fonksiyon
void testAt() {
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    assert(array.at(0) == 1);
    assert(array.at(1) == 2);
    assert(array.at(2) == 3);

    try {
        array.at(-1);
        array.at(3);
    } catch (const std::out_of_range& e) {
        std::cerr << "at() Testi Başarılı." << std::endl;
        return;
    }
    std::cerr << "at() Testi Hatası: Beklenen std::out_of_range hatası yakalanmadı." << std::endl;
}

// insert() methodunu test eden fonksiyon
void testInsert() {
    DynamicArray<int> array;
    array.insert(0, 1);
    array.insert(1, 2);
    array.insert(2, 3);

    assert(array.at(0) == 1);
    assert(array.at(1) == 2);
    assert(array.at(2) == 3);

    array.insert(2, 4);
    assert(array.at(0) == 1);
    assert(array.at(1) == 2);
    assert(array.at(2) == 4);
    assert(array.at(3) == 3);

    try {
        array.insert(-1, 1);
        array.insert(4, 2);
    } catch (const std::out_of_range& e) {
        std::cerr << "insert() Testi Başarılı." << std::endl;
        return;
    }
    std::cerr << "insert() Testi Hatası: Beklenen std::out_of_range hatası yakalanmadı." << std::endl;
}

// erase() methodunu test eden fonksiyon
void testErase() {
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    array.erase(0);
    assert(array.at(0) == 2 && array.at(1) == 3);

    array.erase(1);
    assert(array.at(0) == 2);

    array.erase(0);
    assert(array.getSize() == 0 && array.isEmpty());

    try {
        array.erase(0);
    } catch (const std::out_of_range& e) {
        std::cerr << "erase() Testi Başarılı." << std::endl;
        return;
    }
    std::cerr << "erase() Testi Hatası: Beklenen std::out_of_range hatası yakalanmadı." << std::endl;
}

// Farklı veri türleriyle test eden fonksiyon
void testWithDifferentTypes() {
    DynamicArray<int> intArray;
    intArray.push_back(1);
    intArray.push_back(2);
    intArray.push_back(3);
    assert(intArray.at(0) == 1 && intArray.at(1) == 2 && intArray.at(2) == 3);

    DynamicArray<std::string> stringArray;
    stringArray.push_back("Hello");
    stringArray.push_back("World");
    stringArray.push_back("!");
    assert(stringArray.at(0) == "Hello" && stringArray.at(1) == "World" && stringArray.at(2) == "!");

    std::cerr << "Farklı Veri Türleriyle Testi Başarılı." << std::endl;
}