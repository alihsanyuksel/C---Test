#include <iostream>
#include <cassert>
#include <cmath> // For fabs
#include <sstream> // For stringstream

#include "Complex.h"

// Tolerance for floating-point comparisons
const double EPSILON = 1e-9;

void testConstructors() {
    Complex c1;
    assert(std::fabs(c1.getReal() - 0.0) < EPSILON);
    assert(std::fabs(c1.getImag() - 0.0) < EPSILON);
    std::cout << "testConstructors (default) passed.\n";

    Complex c2(3.0, 4.0);
    assert(std::fabs(c2.getReal() - 3.0) < EPSILON);
    assert(std::fabs(c2.getImag() - 4.0) < EPSILON);
    std::cout << "testConstructors (parameterized) passed.\n";
}

void testGetters() {
    Complex c(5.2, -1.7);
    assert(std::fabs(c.getReal() - 5.2) < EPSILON);
    assert(std::fabs(c.getImag() - (-1.7)) < EPSILON);
    std::cout << "testGetters passed.\n";
}

void testAddition() {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, -1.0);
    Complex c3 = c1 + c2;
    assert(std::fabs(c3.getReal() - 4.0) < EPSILON);
    assert(std::fabs(c3.getImag() - 1.0) < EPSILON);
    std::cout << "testAddition passed.\n";
}

void testSubtraction() {
    Complex c1(5.0, 3.0);
    Complex c2(2.0, 1.0);
    Complex c3 = c1 - c2;
    assert(std::fabs(c3.getReal() - 3.0) < EPSILON);
    assert(std::fabs(c3.getImag() - 2.0) < EPSILON);
    std::cout << "testSubtraction passed.\n";
}

void testMultiplication() {
    Complex c1(2.0, 3.0);
    Complex c2(4.0, -1.0);
    Complex c3 = c1 * c2;
    assert(std::fabs(c3.getReal() - 11.0) < EPSILON);
    assert(std::fabs(c3.getImag() - 10.0) < EPSILON);
    std::cout << "testMultiplication passed.\n";
}

void testDivision() {
    Complex c1(10.0, 5.0);
    Complex c2(2.0, 1.0);
    Complex c3 = c1 / c2;
    assert(std::fabs(c3.getReal() - 5.0) < EPSILON);
    assert(std::fabs(c3.getImag() - 0.0) < EPSILON);
    std::cout << "testDivision passed.\n";

    try {
        Complex c4(0.0, 0.0);
        c1 / c4; // Division by zero
        assert(false); // Should throw exception
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Division by zero");
        std::cout << "testDivision (division by zero exception) passed.\n";
    }
}

void testEquality() {
    Complex c1(2.5, -3.2);
    Complex c2(2.5, -3.2);
    Complex c3(1.0, 4.0);
    assert(c1 == c2);
    assert(c1 != c3);
    std::cout << "testEquality passed.\n";
}

void testOutputStream() {
    Complex c1(3.0, 4.0);
    std::stringstream ss1;
    ss1 << c1;
    assert(ss1.str() == "3+4i");

    Complex c2(2.0, -1.0);
    std::stringstream ss2;
    ss2 << c2;
    assert(ss2.str() == "2-1i");

    Complex c3(0.0, 5.0);
    std::stringstream ss3;
    ss3 << c3;
    assert(ss3.str() == "0+5i");

        Complex c4(0.0, -5.0);
    std::stringstream ss4;
    ss4 << c4;
    assert(ss4.str() == "0-5i");
    std::cout << "testOutputStream passed.\n";
}

int main() {
    testConstructors();
    testGetters();
    testAddition();
    testSubtraction();
    testMultiplication();
    testDivision();
    testEquality();
    testOutputStream();

    std::cout << "All tests finished.\n";
    return 0;
}