#include <iostream>
#include "Complex.h"
#include <cassert>
#include <limits>

int main() {
    // Constructors: Varsayılan yapılandırıcı ve parametreli yapılandırıcı
    Complex defaultComplex;
    assert(std::abs(defaultComplex.getReal() - 0.0) < 1e-9 && std::abs(defaultComplex.getImag() - 0.0) < 1e-9);
    
    Complex complexA(2.0, 3.0);
    assert(std::abs(complexA.getReal() - 2.0) < 1e-9 && std::abs(complexA.getImag() - 3.0) < 1e-9);
    
    std::cout << "Constructors test passed." << std::endl;
    
    // Getters
    assert(std::abs(complexA.getReal() - 2.0) < 1e-9);
    assert(std::abs(complexA.getImag() - 3.0) < 1e-9);
    
    std::cout << "Getters test passed." << std::endl;
    
    // Toplama (+)
    Complex complexB(1.0, 4.0);
    Complex sum = complexA + complexB;
    assert(std::abs(sum.getReal() - 3.0) < 1e-9 && std::abs(sum.getImag() - 7.0) < 1e-9);
    
    std::cout << "Addition test passed." << std::endl;
    
    // Çıkarma (-)
    Complex difference = complexA - complexB;
    assert(std::abs(difference.getReal() - 1.0) < 1e-9 && std::abs(difference.getImag() + 1.0) < 1e-9);

    
    std::cout << "Subtraction test passed." << std::endl;
    
    // Çarpma (*)
    Complex product = complexA * complexB;
    assert(std::abs(product.getReal() - (2.0 * 1.0 - 3.0 * 4.0)) < 1e-9 &&
           std::abs(product.getImag() - (2.0 * 4.0 + 3.0 * 1.0)) < 1e-9);
    
    std::cout << "Multiplication test passed." << std::endl;
    
    // Bölme (/), sıfıra bölme hata durumu
    Complex complexC(1.0, 1.0);
try {
    Complex quotient = complexA / complexB; // Valid division test
    assert(std::abs(quotient.getReal() - (2.0 * 1.0 + 3.0 * 4.0) / (1.0 * 1.0 + 4.0 * 4.0)) < 1e-9 &&
           std::abs(quotient.getImag() - (3.0 * 1.0 - 2.0 * 4.0) / (1.0 * 1.0 + 4.0 * 4.0)) < 1e-9);

    // Division by zero test
    Complex complexZero(0.0, 0.0);
    Complex invalidQuotient = complexA / complexZero;
    assert(false && "Expected an exception for division by zero");
} catch (const std::runtime_error& e) {
    assert(std::string(e.what()) == "Division by zero" && "Incorrect exception message");
} catch (...) {
    assert(false && "Unexpected error during division by zero");
}
    
    std::cout << "Division test passed." << std::endl;
    
    // Eşitlik (==) ve Eşitsizlik (!=)
    Complex complexD(2.0, 3.0);
    assert(complexA == complexD);
    assert(complexA != complexB);
    
    std::cout << "Equality test passed." << std::endl;
    
    // Output Stream (<<)
    std::cout << complexA << "\n" // Output should be "2+3i"
              << complexB << "\n" // Output should be "1+4i"
              << complexC << "\n" // Output should be "1+1i"
              << defaultComplex << "\n" // Output should be "0+0i"
              << complexD << std::endl; // Output should be "2+3i"
    
    std::cout << "Output stream test passed." << std::endl;
    
    std::cout << "All tests passed." << std::endl;

    return 0;
}