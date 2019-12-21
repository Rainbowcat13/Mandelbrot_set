#ifndef MANDELBROT_COMPLEX_H
#define MANDELBROT_COMPLEX_H

#include <cmath>
#include <ostream>

class Complex {
    double real, complex;

public:
    Complex operator+(const Complex &other);
    Complex operator*(const Complex &other);
    Complex(double a, double b);
    Complex();
    double getComplex() const;
    double getReal() const;
};

std::ostream& operator<<(std::ostream &out, const Complex &a);
bool operator<(const Complex&a, const Complex &b);
double fabs(const Complex &a);

#endif //MANDELBROT_COMPLEX_H
