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

    //Ürünlerin toplam fiyatını dönüyor.
    double getTotalPrice() const {
        double total = 0.0;
        for(const auto& product : products){
            total += product.price;
        }
        return total;
    }
};

// Ürün oluşturma testleri
void testProductCreation() {
    Product p1(1, "Laptop", 999.99);
    assert(p1.id == 1);
    assert(p1.name == "Laptop");
    assert(p1.price == 999.99);
    std::cout << "testProductCreation: Geçti" << std::endl;
}

// Ürün ekleme ve bulma testleri
void testAddAndFindProduct() {
    ProductManager pm;
    Product p1(1, "Laptop", 999.99);
    pm.addProduct(p1);
    Product* foundProduct = pm.findProduct(1);
    assert(foundProduct != nullptr);
    assert(foundProduct->id == 1);
    assert(foundProduct->name == "Laptop");
    assert(foundProduct->price == 999.99);
    std::cout << "testAddAndFindProduct: Geçti" << std::endl;

    foundProduct = pm.findProduct(2); // Var olmayan bir ürünü bulma
    assert(foundProduct == nullptr);
    std::cout << "testAddAndFindProduct: Geçti" << std::endl;
}

// Ürün kaldırma testleri
void testRemoveProduct() {
    ProductManager pm;
    Product p1(1, "Laptop", 999.99);
    pm.addProduct(p1);
    assert(pm.findProduct(1) != nullptr);
    pm.removeProduct(1);
    assert(pm.findProduct(1) == nullptr);
    std::cout << "testRemoveProduct: Geçti" << std::endl;

    assert(!pm.removeProduct(1)); // Var olmayan bir ürünü kaldırma
    std::cout << "testRemoveProduct: Geçti" << std::endl;
}

// Tüm ürünleri alma testleri
void testGetAllProducts() {
    ProductManager pm;
    pm.addProduct(Product(1, "Laptop", 999.99));
    pm.addProduct(Product(2, "Smartphone", 499.99));
    pm.addProduct(Product(3, "Tablet", 299.99));

    std::vector<Product> products = pm.getAllProducts();
    assert(products.size() == 3);
    assert(products[0].id == 1 && products[0].name == "Laptop" && products[0].price == 999.99);
    assert(products[1].id == 2 && products[1].name == "Smartphone" && products[1].price == 499.99);
    assert(products[2].id == 3 && products[2].name == "Tablet" && products[2].price == 299.99);
    std::cout << "testGetAllProducts: Geçti" << std::endl;
}

// Toplam fiyat hesapla testleri
void testGetTotalPrice() {
    ProductManager pm;
    pm.addProduct(Product(1, "Laptop", 999.99));
    pm.addProduct(Product(2, "Smartphone", 499.99));
    pm.addProduct(Product(3, "Tablet", 299.99));

    double totalPrice = pm.getTotalPrice();
    assert(totalPrice == 1799.97);
    std::cout << "testGetTotalPrice: Geçti" << std::endl;

    pm.removeAllProducts(); // Yalnızca tamamlama için, kullanıcı tarafından tanımlanmamış
    totalPrice = pm.getTotalPrice();
    assert(totalPrice == 0.0);
    std::cout << "testGetTotalPrice: Geçti" << std::endl;
}

// Tüm testleri çalıştır
int main() {
    testProductCreation();
    testAddAndFindProduct();
    testRemoveProduct();
    testGetAllProducts();
    testGetTotalPrice();

    std::cout << "Tüm testler başarıyla geçti." << std::endl;

    return 0;
}