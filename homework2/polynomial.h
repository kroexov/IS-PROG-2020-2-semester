#ifndef INC_2_POLYNOMIAL_H
#define INC_2_POLYNOMIAL_H

#include <sstream>
#include<iostream>
#include<math.h>


class Polynomial {
public:
    int min = 0;
    int max = 0;
    int *degrees = nullptr;
public:

    Polynomial();

    Polynomial(int min, int max, int coefficients[]);

    ~Polynomial();

    Polynomial(const Polynomial &polynom);

    Polynomial &operator=(const Polynomial &polynom);

    friend std::ostream &operator<<(std::ostream &out, const Polynomial &polynom);

    friend bool operator==(const Polynomial &polynom, const Polynomial &polynom2);

    Polynomial &operator*=(const Polynomial &polynom);

    Polynomial &operator*(const Polynomial &polynom) const;

    Polynomial &operator+=(const Polynomial &polynom);

    Polynomial &operator+(const Polynomial &polynom) const;

    Polynomial &operator/=(const int &k);

    Polynomial &operator/(int k) const;

    friend Polynomial operator-(const Polynomial &polynom);

    friend Polynomial operator*(int k, const Polynomial &polynom);

    friend Polynomial operator*(const Polynomial &polynom, int k);

    int operator[](int k) const;

    int &operator[](int k);

    double get(int k);

};

#endif