// trinarynumber.h
// TrinaryNumber class with overloaded operators.

#ifndef TRINARYINTERPRETER_TRINARYNUMBER_H_
#define TRINARYINTERPRETER_TRINARYNUMBER_H_

#include <string>

class TrinaryNumber {
    int value_;

public:
    TrinaryNumber(std::string);
    TrinaryNumber(int);
    
    // Converts decimal value_ to trinary and returns string representation.
    std::string GetTrinary() const;

    int GetDecimal() const {
        return value_;
    }

    // Checks if number can be used in logical operations.
    bool IsLogical() const;

    friend TrinaryNumber operator+(const TrinaryNumber&, const TrinaryNumber&);
    friend TrinaryNumber operator-(const TrinaryNumber&, const TrinaryNumber&);
    friend TrinaryNumber operator*(const TrinaryNumber&, const TrinaryNumber&);

    friend TrinaryNumber operator&(const TrinaryNumber&, const TrinaryNumber&);
    friend TrinaryNumber operator|(const TrinaryNumber&, const TrinaryNumber&);
    friend TrinaryNumber operator~(const TrinaryNumber&);

    friend TrinaryNumber operator==(const TrinaryNumber&, const TrinaryNumber&);
    friend TrinaryNumber operator!=(const TrinaryNumber&, const TrinaryNumber&);
    friend TrinaryNumber operator>(const TrinaryNumber&, const TrinaryNumber&);
    friend TrinaryNumber operator<(const TrinaryNumber&, const TrinaryNumber&);
    friend TrinaryNumber operator<=(const TrinaryNumber&, const TrinaryNumber&);
    friend TrinaryNumber operator>=(const TrinaryNumber&, const TrinaryNumber&);
};

#endif