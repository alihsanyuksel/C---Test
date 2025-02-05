#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits> // Required for numeric_limits
#include <stdexcept> // For exceptions

struct Product {
    std::string name;
    double price;
    int quantity;
};

std::vector<Product> loadProductsFromFile(const std::string& filename) {
    std::vector<Product> products;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string line;
    int lineNumber = 1;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        Product product;

        if (!(ss >> product.name >> product.price >> product.quantity)) {
            throw std::runtime_error("Error parsing line " + std::to_string(lineNumber) + ": " + line);
        }

        if (product.price < 0) {
            throw std::runtime_error("Error in line " + std::to_string(lineNumber) + ": Price cannot be negative.");
        }

        if (product.quantity < 0) {
            throw std::runtime_error("Error in line " + std::to_string(lineNumber) + ": Quantity cannot be negative.");
        }

        products.push_back(product);
        lineNumber++;
    }

    if (inputFile.fail() && !inputFile.eof()) {
        throw std::runtime_error("Error reading file: " + filename); // Check for read errors
    }

    inputFile.close();
    return products;
}

void saveProductsToFile(const std::string& filename, const std::vector<Product>& products) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Error opening output file: " + filename);
    }

    for (const auto& product : products) {
        outputFile << product.name << " " << product.price << " " << product.quantity << std::endl;
        if (outputFile.fail()) { // Check for write errors after each write
            throw std::runtime_error("Error writing to file: " + filename);
        }
    }

    outputFile.close();

    if(outputFile.fail()){
        throw std::runtime_error("Error closing the file: " + filename);
    }
}

int main() {
    try {
        std::vector<Product> products = loadProductsFromFile("products.txt");

        if(products.empty()){
            std::cout << "No products loaded." << std::endl;
        } else {
            for (const auto& product : products) {
                std::cout << product.name << " " << product.price << " " << product.quantity << std::endl;
            }

            saveProductsToFile("output.txt", products);
        }

    } catch (const std::runtime_error& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1; // Indicate failure
    }

    return 0; // Indicate success
}