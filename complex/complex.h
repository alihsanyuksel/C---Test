#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

#include "Complex.cpp"

#endif