#include "polynomial.h"

Polynomial::Polynomial() = default;

//todo default doesnt work
Polynomial::~Polynomial() = default;

Polynomial::Polynomial(int minimal, int maximal, int *coefficients) : min(minimal), max(maximal) {
    degrees = new int[max - min + 1];
    if (coefficients == nullptr)
        degrees = nullptr;
    else {
        for (int i = 0; i < max - min + 1; i++) {
            degrees[i] = coefficients[i];
        }
    }
}

int *degreeupper(const int *coeffs, int size) {
    if (coeffs == nullptr)
        return nullptr;
    int *result = new int[size];
    for (int i = 0; i < size; ++i) {
        result[i] = coeffs[i];
    }
    return result;
}

Polynomial::Polynomial(const Polynomial &polynom)
        : min(polynom.min), max(polynom.max), degrees(degreeupper(polynom.degrees, polynom.max - polynom.min + 1)) {}


//todo = doesnt work
Polynomial &Polynomial::operator=(const Polynomial &polynom) = default;

bool operator==(const Polynomial &first, const Polynomial &second) {
    if (first.degrees == nullptr and second.degrees == nullptr)
        return true;
    for (int i = 0; i < first.max - first.min + 1; i++) {
        if (first.degrees[i] != second.degrees[i] and first.degrees[i] != 0 and second.degrees[i] != 0)
            return false;
    }
    return true;
}

Polynomial operator*(const int k, const Polynomial &polynom) {
    int *result = new int[polynom.max - polynom.min + 1];
    for (int i = 0; i < polynom.max - polynom.min + 1; ++i) {
        result[i] = polynom.degrees[i];
        result[i] *= k;
    }
    //todo memory-leak
    return Polynomial(polynom.min, polynom.max, result);
}

Polynomial operator*(const Polynomial &polynom, const int k) {
    return k * polynom;
}

int Polynomial::operator[](int k) const {
    if (k < min or k > max or degrees == nullptr)
        return 0;
    return degrees[k - min];
}

int &Polynomial::operator[](int k) {
    k++;
    int *newdegrees = new int[k - min + 1];
    for (int i = 0; i < max - min + 1; i++) {
        newdegrees[i] = degrees[i];
    }
    for (int i = max - min + 1; i <= k; i++) {
        newdegrees[i] = 0;
    }
    delete[] degrees;
    degrees = newdegrees;
    max = k - 1;
    return degrees[k];
}

//todo get O(n)
double Polynomial::get(int k) {
    if (degrees == nullptr)
        return 0;
    double result = 0;
    for (int i = min; i <= max; i++) {
        result += degrees[i - min] * pow(k, i);
    }
    return result;
}

Polynomial &Polynomial::operator/=(const int &k) {

	//todo for_each
    for (int i = 0; i < max - min + 1; i++) {
        degrees[i] /= k;
    }
    //todo make function for it
    int i = 0;
    bool not_null = false;
    while (!not_null) {
        if (degrees[i] == 0) {
            i++;
            min++;
        } else
            not_null = true;
    }
    int from = i;
    i = max - min + 1;
    not_null = false;
    while (!not_null) {
        if (degrees[i] == 0) {
            i--;
            max--;
        } else
            not_null = true;
    }
    i = 0;
    int to = i;
    int *resulted = new int[max - min + 1];
    for (int j = 0; j <= to - from + 1; ++j) {
        resulted[j] = degrees[j + from];
    }
    delete[] degrees;
    degrees = resulted;
    return *this;
}

Polynomial &Polynomial::operator/(int k) const {
    Polynomial result(*this);
    return result /= k;
}

Polynomial operator-(const Polynomial &polynom) {
    int *result = new int[polynom.max - polynom.min + 1];
    for (int i = 0; i < polynom.max - polynom.min + 1; ++i) {
        result[i] = -polynom.degrees[i];
    }
    return Polynomial(polynom.min, polynom.max, result);
}


//todo * from *=
Polynomial &Polynomial::operator*=(const Polynomial &polynom) {
    *this = *this * polynom;
    return *this;
}

Polynomial operator*(const Polynomial &left, const Polynomial &right) {

    if (left.degrees == nullptr or right.degrees == nullptr) {
        return Polynomial(0, 0, nullptr);
    }
    int newmin = left.min + right.min;
    int newmax = left.max + right.max;
    int *newdegrees = new int[newmax - newmin + 1]{0};
    for (int i = left.min; i <= left.max; i++) {
        for (int j = right.min; j <= right.max; j++) {
            newdegrees[i + j - newmin] += left.degrees[i - left.min] * right.degrees[j - right.min];
        }
    }
    return Polynomial(newmin, newmax, newdegrees);
}

Polynomial &Polynomial::operator+=(const Polynomial &polynom) {
    *this = *this + polynom;
    return *this;
}

Polynomial operator+(const Polynomial &left, const Polynomial &right) {
    if (left.degrees == nullptr and right.degrees == nullptr)
        return Polynomial(0, 0, nullptr);

    else if (left.degrees == nullptr)
        return Polynomial(right.min, right.max, right.degrees);

    else if (right.degrees == nullptr)
        return Polynomial(left.min, left.max, left.degrees);

    int newmin = std::min(left.min, right.min);
    int newmax = std::max(left.max, right.max);
    int *newdegrees = new int[newmax - newmin + 1];
    for (int i = left.min; i <= left.max; i++)
        newdegrees[i - newmin] += left.degrees[i - left.min];
    for (int j = right.min; j <= right.max; j++)
        newdegrees[j - newmin] += right.degrees[j - right.min];

    return Polynomial(newmin, newmax, newdegrees);
}

std::ostream &operator<<(std::ostream &out, const Polynomial &polynom) {
    if (polynom.degrees == nullptr) {
        out << 0;
        return out;
    }
    switch (polynom.max) {
        case 0:
            if (polynom.degrees[polynom.max - polynom.min] == 0) {
                if (polynom.max == 0 and polynom.min == 0)
                    out << "0";
                else
                    out << "";
            } else
                out << polynom.degrees[polynom.max - polynom.min];
            break;
        case 1:
            if (polynom.degrees[polynom.max - polynom.min] == 0)
                out << "";
            else if (abs(polynom.degrees[polynom.max - polynom.min]) == 1)
                out << ((polynom.degrees[polynom.max - polynom.min] < 0) ? "-x" : "x");
            else
                out << polynom.degrees[polynom.max - polynom.min] << "x";
            break;
        default:
            if (polynom.degrees[polynom.max - polynom.min] == 0)
                out << "";
            else if (abs(polynom.degrees[polynom.max - polynom.min]) == 1)
                out << ((polynom.degrees[polynom.max - polynom.min] < 0) ? "-x^" : "x^") << polynom.max;
            else
                out << polynom.degrees[polynom.max - polynom.min] << "x^" << polynom.max;
            break;
    }
    for (int i = polynom.max - 1; i >= polynom.min; i--) {
        switch (i) {
            case 0:
                if (polynom.degrees[i - polynom.min] == 0)
                    out << "";
                else
                    out << ((polynom.degrees[i - polynom.min] < 0) ? "" : "+") << polynom.degrees[i - polynom.min];
                break;
            case 1:
                if (polynom.degrees[i - polynom.min] == 0)
                    out << "";
                else if (abs(polynom.degrees[i - polynom.min]) == 1)
                    out << ((polynom.degrees[i - polynom.min] < 0) ? "-x" : "+x");
                else
                    out << ((polynom.degrees[i - polynom.min] < 0) ? "" : "+") << polynom.degrees[i - polynom.min]
                        << "x";
                break;
            default:
                if (polynom.degrees[i - polynom.min] == 0)
                    out << "";
                else if (abs(polynom.degrees[i - polynom.min]) == 1)
                    out << ((polynom.degrees[i - polynom.min] < 0) ? "-x^" : "+x^") << i;
                else
                    out << ((polynom.degrees[i - polynom.min] < 0) ? "" : "+") << polynom.degrees[i - polynom.min]
                        << "x^" << i;
                break;
        }
    }
    return out;
}
