#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Item {
    std::string name;
    int quantity;
    double price;
};

int main() {
    std::vector<Item*> inventory; // Store pointers to items

    // Add some items
    inventory.push_back(new Item{"Shirt", 10, 20.0});
    inventory.push_back(new Item{"Pants", 5, 30.0});
    inventory.push_back(new Item{"Shoes", 3, 50.0});

    // Calculate total value (potential memory leak and double free)
    double totalValue = 0;
    for (size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i]->quantity > 0) {
            totalValue += inventory[i]->quantity * inventory[i]->price;
        }
        if (inventory[i]->name == "Shoes"){
            delete inventory[i];
            inventory.erase(inventory.begin() + i);
        }
    }
    std::cout << "Total Value: " << totalValue << std::endl;

    //Print inventory (use after free)
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << inventory[i]->name << std::endl;
    }

    // Attempt to free memory (double free)
    for (size_t i = 0; i < inventory.size(); ++i) {
        delete inventory[i];
    }
    inventory.clear();

    return 0;
}