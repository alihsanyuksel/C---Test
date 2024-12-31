#include <iostream>
#include <cassert>
#include <cmath> // For std::sqrt
#include "Complex.h"

int main() {
    try {
        // Constructors
        Complex c1; // Default constructor
        assert(c1.getReal() == 0.0 && c1.getImag() == 0.0, "Default constructor failed");

        Complex c2(3.0, 4.0); // Parameterized constructor
        assert(c2.getReal() == 3.0 && c2.getImag() == 4.0, "Parameterized constructor failed");

        // Getters
        assert(c2.getReal() == 3.0, "getReal() failed");
        assert(c2.getImag() == 4.0, "getImag() failed");

        // Addition (+)
        Complex c3(1.0, 2.0);
        Complex c4 = c2 + c3;
        assert(c4.getReal() == 4.0 && c4.getImag() == 6.0, "Addition failed");

        // Subtraction (-)
        Complex c5 = c2 - c3;
        assert(c5.getReal() == 2.0 && c5.getImag() == 2.0, "Subtraction failed");

        // Multiplication (*)
        Complex c6 = c2 * c3;
        assert(std::abs(c6.getReal() - -11.0) < 1e-9 && std::abs(c6.getImag() - 2.0) < 1e-9, "Multiplication failed");

        // Division (/)
        Complex c7(1.0, 1.0);
        Complex c8 = c2 / c7;
        assert(std::abs(c8.getReal() - 2.0) < 1e-9 && std::abs(c8.getImag() - 2.0) < 1e-9, "Division failed");

        // Division by zero
        try {
            Complex c9 = c2 / Complex(0.0, 0.0);
            assert(false, "Division by zero should throw an exception");
        } catch (const std::runtime_error& e) {
            assert(std::string(e.what()) == "Division by zero", "Division by zero exception message incorrect");
        }

        // Equality (==) and Inequality (!=)
        Complex c10(3.0, 4.0);
        Complex c11(5.0, 6.0);
        assert(c2 == c10, "Equality failed");
        assert(c2 != c11, "Inequality failed");

        // Output Stream (<<)
        std::ostringstream oss;
        oss << c2;
        assert(oss.str() == "3+4i", "Output stream failed");

        Complex c12(2.0, -1.0);
        oss.str("");
        oss << c12;
        assert(oss.str() == "2-1i", "Output stream failed");

        Complex c13(0.0, 5.0);
        oss.str("");
        oss << c13;
        assert(oss.str() == "0+5i", "Output stream failed");

        std::cout << "All tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}