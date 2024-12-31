#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Ürünü temsil ediyor.
struct Product {
    int id;
    std::string name;
    double price;

    Product(int id, const std::string& name, double price) : id(id), name(name), price(price) {}

    void print() const {
        std::cout << "ID: " << id << ", Name: " << name << ", Price: $" << price << std::endl;
    }
};

// Ürün Yönetimi sınıfı
class ProductManager {
private:
    std::vector<Product> products;

public:
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    // Bir ürünü id'si ile bulup bir pointer dönüyor bulamazsa nullptr dönüyor.
    Product* findProduct(int id) {
        for (auto& product : products) {
            if (product.id == id) {
                return &product;
            }
        }
        return nullptr;
    }

    // Ürünü silen metod
    bool removeProduct(int id) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->id == id) {
                products.erase(it);
                return true;
            }
        }
        return false;
    }

    // Tüm ürünleri dönen metod
    const std::vector<Product>& getAllProducts() const {
        return products;
    }

    // Ürünlerin toplam fiyatını dönüyor.
    double getTotalPrice() const {
        double total = 0.0;
        for (const auto& product : products) {
            total += product.price;
        }
        return total;
    }
};

// Ürün oluşturma testleri
void testProductCreation() {
    Product product1(1, "Laptop", 999.99);
    Product product2(2, "Smartphone", 499.99);

    assert(product1.id == 1 && product1.name == "Laptop" && product1.price == 999.99);
    assert(product2.id == 2 && product2.name == "Smartphone" && product2.price == 499.99);
    std::cout << "Ürün Oluşturma Testleri: Geçti" << std::endl;
}

// Ürün ekleme ve bulma testleri
void testAddAndFindProduct() {
    ProductManager manager;
    Product product(1, "Laptop", 999.99);

    manager.addProduct(product);
    Product* foundProduct = manager.findProduct(1);

    assert(foundProduct != nullptr);
    if (foundProduct) {
        assert(foundProduct->id == 1 && foundProduct->name == "Laptop" && foundProduct->price == 999.99);
    }

    Product* nonExistentProduct = manager.findProduct(3);
    assert(nonExistentProduct == nullptr);

    std::cout << "Ürün Ekleme ve Bulma Testleri: Geçti" << std::endl;
}

// Ürün kaldırma testleri
void testRemoveProduct() {
    ProductManager manager;
    Product product1(1, "Laptop", 999.99);
    Product product2(2, "Smartphone", 499.99);

    manager.addProduct(product1);
    manager.addProduct(product2);

    bool removed = manager.removeProduct(1);
    assert(removed == true);

    Product* foundProduct = manager.findProduct(1);
    assert(foundProduct == nullptr);

    removed = manager.removeProduct(3);
    assert(removed == false);

    std::cout << "Ürün Kaldırma Testleri: Geçti" << std::endl;
}

// Tüm ürünleri alma testleri
void testGetAllProducts() {
    ProductManager manager;
    Product product1(1, "Laptop", 999.99);
    Product product2(2, "Smartphone", 499.99);

    manager.addProduct(product1);
    manager.addProduct(product2);

    const std::vector<Product>& products = manager.getAllProducts();
    assert(products.size() == 2);

    assert(products[0].id == 1 && products[0].name == "Laptop" && products[0].price == 999.99);
    assert(products[1].id == 2 && products[1].name == "Smartphone" && products[1].price == 499.99);

    std::cout << "Tüm Ürünleri Alma Testleri: Geçti" << std::endl;
}

// Toplam fiyat hesaplama testleri
void testGetTotalPrice() {
    ProductManager manager;
    Product product1(1, "Laptop", 999.99);
    Product product2(2, "Smartphone", 499.99);
    Product product3(3, "Headphones", 199.99);

    manager.addProduct(product1);
    manager.addProduct(product2);
    manager.addProduct(product3);

    double totalPrice = manager.getTotalPrice();
    assert(totalPrice == 1699.97);

    manager.removeProduct(3);
    totalPrice = manager.getTotalPrice();
    assert(totalPrice == 1499.98);

    std::cout << "Toplam Fiyat Hesaplama Testleri: Geçti" << std::endl;
}

// Tüm testleri çalıştıran ana fonksiyon
int main() {
    testProductCreation();
    testAddAndFindProduct();
    testRemoveProduct();
    testGetAllProducts();
    testGetTotalPrice();

    std::cout << "Tüm testler başarıyla tamamlandı." << std::endl;
    return 0;
}