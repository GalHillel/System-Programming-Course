#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex
{
public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex operator+(const Complex &other) const
    {
        return Complex(real + other.real, imag + other.imag);
    }

    friend std::ostream &operator<<(std::ostream &os, const Complex &comp)
    {
        os << comp.real << " + " << comp.imag << "i";
        return os;
    }

    // Overloading the equality operator
    bool operator==(const Complex &other) const
    {
        return real == other.real && imag == other.imag;
    }

    // Overloading the greater than operator
    bool operator>(const Complex &other) const
    {
        return (real > other.real) || (real == other.real && imag > other.imag);
    }

    // Overloading the not equal operator
    bool operator!=(const Complex &other) const
    {
        return !(*this == other);
    }


    bool operator<(const Complex &other) const
    {
        return !(*this > other) && !(*this == other);
    }

    bool operator>=(const Complex &other) const
    {
        return !(*this < other);
    }

    bool operator<=(const Complex &other) const
    {
        return !(*this > other);
    }

    double getReal() const { return real; }
    double getImag() const { return imag; }

private:
    double real, imag;
};

#endif
