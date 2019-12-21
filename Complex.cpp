#include "Complex.h"

Complex Complex::operator+(const Complex &other) {
    return {real + other.real, complex + other.complex};
}

Complex::Complex(double a, double b) {
    real = a;
    complex = b;
}

Complex Complex::operator*(const Complex &other) {
    return {real * other.real - complex * other.complex,
            complex * other.real + real * other.complex};
}

double Complex::getReal() const {
    return real;
}

double Complex::getComplex() const {
    return complex;
}


std::ostream& operator<<(std::ostream &out, const Complex &a) {
    out << a.getReal() << " + " << a.getComplex() << "i";
    return out;
}

bool operator<(const Complex&a, const Complex &b) {
    return a.getReal() < b.getReal() ||
        (a.getReal() == b.getReal() && a.getComplex() < b.getComplex());
}

double fabs(const Complex &a) {
    return a.getReal() * a.getReal() + a.getComplex() * a.getComplex();
}

Complex::Complex() {
    real = 0;
    complex = 0;
}