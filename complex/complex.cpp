#include "Complex.h"
#include <cmath> // For std::pow and std::sqrt

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    double r = real * other.real - imag * other.imag;
    double i = real * other.imag + imag * other.real;
    return Complex(r, i);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = std::pow(other.real, 2) + std::pow(other.imag, 2);
    if (denominator == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    double r = (real * other.real + imag * other.imag) / denominator;
    double i = (imag * other.real - real * other.imag) / denominator;
    return Complex(r, i);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) {
        os << "+";
    }
    os << c.imag << "i";
    return os;
}