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

// Test functions
void testProductCreation() {
    Product p(1, "Test Product", 99.99);
    assert(p.id == 1);
    assert(p.name == "Test Product");
    assert(p.price == 99.99);
    std::cout << "testProductCreation passed.\n";
}

void testAddAndFindProduct() {
    ProductManager manager;
    Product p1(1, "Product 1", 10.0);
    manager.addProduct(p1);

    Product* found = manager.findProduct(1);
    assert(found != nullptr);
    assert(found->name == "Product 1");

    Product* notFound = manager.findProduct(99);
    assert(notFound == nullptr);
    std::cout << "testAddAndFindProduct passed.\n";
}

void testRemoveProduct() {
    ProductManager manager;
    Product p1(1, "Product 1", 10.0);
    manager.addProduct(p1);

    assert(manager.removeProduct(1));
    assert(manager.findProduct(1) == nullptr);
    assert(!manager.removeProduct(99)); // Remove non-existent product
    std::cout << "testRemoveProduct passed.\n";
}

void testGetAllProducts() {
    ProductManager manager;
    Product p1(1, "Product 1", 10.0);
    Product p2(2, "Product 2", 20.0);
    manager.addProduct(p1);
    manager.addProduct(p2);

    const std::vector<Product>& allProducts = manager.getAllProducts();
    assert(allProducts.size() == 2);
    assert(allProducts[0].name == "Product 1");
    assert(allProducts[1].price == 20.0);
    std::cout << "testGetAllProducts passed.\n";
}

void testGetTotalPrice() {
    ProductManager manager;
    Product p1(1, "Product 1", 10.0);
    Product p2(2, "Product 2", 20.0);
    Product p3(3, "Product 3", 30.0);

    manager.addProduct(p1);
    manager.addProduct(p2);
    manager.addProduct(p3);

    assert(manager.getTotalPrice() == 60.0);

    ProductManager emptyManager;
    assert(emptyManager.getTotalPrice() == 0.0);
    std::cout << "testGetTotalPrice passed.\n";
}

int main() {
    testProductCreation();
    testAddAndFindProduct();
    testRemoveProduct();
    testGetAllProducts();
    testGetTotalPrice();

    std::cout << "All tests finished.\n";
    return 0;
}