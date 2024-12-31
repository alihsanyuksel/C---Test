#include <iostream>
#include <vector>
#include <algorithm>

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

int main() {
    ProductManager manager;
    manager.addProduct(Product(1, "Laptop", 1200.0));
    manager.addProduct(Product(2, "Mouse", 25.0));
    manager.addProduct(Product(3, "Keyboard", 75.0));

    Product* foundProduct = manager.findProduct(2);
    if (foundProduct != nullptr) {
        foundProduct->print();
    }

    if (manager.removeProduct(2)) {
      std::cout << "Product 2 removed." << std::endl;
    }
    std::cout << "Total Price: $" << manager.getTotalPrice() << std::endl;

    return 0;
}