#include <iostream>
#include <stdexcept>
#include <cassert>
#include <string>
#include "DynamicArray.h"

void testConstructors() {
    try {
        DynamicArray<int> da;
        assert(da.getSize() == 0);
        assert(da.getCapacity() == 0);
        std::cout << "Varsayılan yapılandırıcı test edildi: Başarılı\n";

        DynamicArray<int> da2(5);
        assert(da2.getSize() == 0);
        assert(da2.getCapacity() == 5);
        std::cout << "Parametrelendirilmiş yapılandırıcı test edildi: Başarılı\n";

        DynamicArray<int> da3(-3);
    } catch (const std::runtime_error& e) {
        std::cout << "Negatif başlangıç kapasitesi için hata yakalandı: " << e.what() << "\n";
        std::cout << "Negatif başlangıç kapasitesi test edildi: Başarılı\n";
    }
}

void testGetSizeAndIsEmpty() {
    DynamicArray<int> da;
    assert(da.getSize() == 0);
    assert(da.isEmpty());
    std::cout << "Varsayılan yapılandırıcı ile getSize() ve isEmpty() test edildi: Başarılı\n";

    DynamicArray<int> da2(5);
    assert(da2.getSize() == 0);
    assert(da2.isEmpty());
    std::cout << "Parametrelendirilmiş yapılandırıcı ile getSize() ve isEmpty() test edildi: Başarılı\n";

    da.push_back(10);
    assert(da.getSize() == 1);
    assert(!da.isEmpty());
    std::cout << "push_back() sonrası getSize() ve isEmpty() test edildi: Başarılı\n";

    da.insert(0, 5);
    assert(da.getSize() == 2);
    assert(!da.isEmpty());
    std::cout << "insert() sonrası getSize() ve isEmpty() test edildi: Başarılı\n";

    da.erase(0);
    assert(da.getSize() == 1);
    assert(!da.isEmpty());
    std::cout << "erase() sonrası getSize() ve isEmpty() test edildi: Başarılı\n";

    da.erase(0);
    assert(da.getSize() == 0);
    assert(da.isEmpty());
    std::cout << "Tüm öğeler silindiğinde isEmpty() test edildi: Başarılı\n";
}

void testGetCapacity() {
    DynamicArray<int> da;
    assert(da.getCapacity() == 0);
    std::cout << "Varsayılan yapılandırıcı ile getCapacity() test edildi: Başarılı\n";

    DynamicArray<int> da2(5);
    assert(da2.getCapacity() == 5);
    std::cout << "Parametrelendirilmiş yapılandırıcı ile getCapacity() test edildi: Başarılı\n";

    da2.push_back(10);
    assert(da2.getCapacity() == 5);
    std::cout << "push_back() sonrası getCapacity() test edildi: Başarılı\n";

    da2.push_back(10);
    da2.push_back(10);
    da2.push_back(10);
    da2.push_back(10);
    da2.push_back(10);
    assert(da2.getCapacity() == 10);
    std::cout << "Kapasite dolduktan sonra getCapacity() test edildi: Başarılı\n";
}

void testPushBack() {
    DynamicArray<int> da;
    da.push_back(10);
    da.push_back(20);
    da.push_back(30);
    assert(da.getSize() == 3);
    assert(da.at(0) == 10);
    assert(da.at(1)== 20);
    assert(da.at(2) == 30);
    std::cout << "push_back() test edildi: Başarılı\n";
}

void testAt() {
    DynamicArray<int> da;
    da.push_back(10);
    da.push_back(20);
    da.push_back(30);
    assert(da.at(0) == 10);
    assert(da.at(1) == 20);
    assert(da.at(2) == 30);
    std::cout << "const ve const olmayan at() test edildi: Başarılı\n";

    try {
        da.at(3); // Geçersiz indis
    } catch (const std::out_of_range& e) {
        std::cout << "Geçersiz indis için hata yakalandı: " << e.what() << "\n";
        std::cout << "Geçersiz indis test edildi: Başarılı\n";
    }

    try {
        da.at(-1); // Negatif indis
    } catch (const std::out_of_range& e) {
        std::cout << "Negatif indis için hata yakalandı: " << e.what() << "\n";
        std::cout << "Negatif indis test edildi: Başarılı\n";
    }
}

void testInsert() {
    DynamicArray<int> da;
    da.insert(0, 10);
    assert(da.at(0) == 10);
    assert(da.getSize() == 1);
    std::cout << "Dizinin başına ekleme test edildi: Başarılı\n";

    da.insert(1, 20);
    assert(da.at(0) == 10);
    assert(da.at(1) == 20);
    assert(da.getSize() == 2);
    std::cout << "Dizinin ortasına ekleme test edildi: Başarılı\n";

    da.insert(2, 30);
    assert(da.at(0) == 10);
    assert(da.at(1) == 20);
    assert(da.at(2)== 30);
    assert(da.getSize() == 3);
    std::cout << "Dizinin sonuna ekleme test edildi: Başarılı\n";

    try {
        da.insert(3, 40); // Geçersiz indis
    } catch (const std::out_of_range& e) {
        std::cout << "Geçersiz indis için hata yakalandı: " << e.what() << "\n";
        std::cout << "Geçersiz indis test edildi: Başarılı\n";
    }

    try {
        da.insert(-1, 40); // Negatif indis
    } catch (const std::out_of_range& e) {
        std::cout << "Negatif indis için hata yakalandı: " << e.what() << "\n";
        std::cout << "Negatif indis test edildi: Başarılı\n";
    }
}

void testErase() {
    DynamicArray<int> da;
    da.push_back(10);
    da.push_back(20);
    da.push_back(30);

    da.erase(0);
    assert(da.at(0) == 20);
    assert(da.at(1) == 30);
    assert(da.getSize() == 2);
    std::cout << "Dizinin başından silme test edildi: Başarılı\n";

    da.erase(1);
    assert(da.at(0) == 20);
    assert(da.getSize() == 1);
    std::cout << "Dizinin ortasından silme test edildi: Başarılı\n";

    da.erase(0);
    assert(da.getSize() == 0);
    std::cout << "Dizinin sonundan silme test edildi: Başarılı\n";

    try {
        da.erase(0); // Geçersiz indis
    } catch (const std::out_of_range& e) {
        std::cout << "Geçersiz indis için hata yakalandı: " << e.what() << "\n";
        std::cout << "Geçersiz indis test edildi: Başarılı\n";
    }

    try {
        da.erase(-1); // Negatif indis
    } catch (const std::out_of_range& e) {
        std::cout << "Negatif indis için hata yakalandı: " << e.what() << "\n";
        std::cout << "Negatif indis test edildi: Başarılı\n";
    }
}
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
int main() {
    std::cout << "DynamicArray Sınıfı Testleri Başladı:\n";

    testConstructors();
    testGetSizeAndIsEmpty();
    testGetCapacity();
    testPushBack();
    testAt();
    testInsert();
    testErase();

    std::cout << "Tüm testler başarılı.\n";
    return 0;
}