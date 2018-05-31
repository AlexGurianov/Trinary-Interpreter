// trinarynumber.cpp

#include <string>

#include "myexceptions.h"
#include "trinarynumber.h"

TrinaryNumber::TrinaryNumber(std::string s) {
    value_ = 0;

    // conversion from trinary to decimal disregarding the leading 0
    for (int pos = 1; pos < static_cast<int>(s.size()); ++pos) {
        value_ *= 3;
        if (s[pos] == '+') {
            value_ += 1;
        } else if (s[pos] == '-') {
            value_ -= 1;
        }
    }
}

TrinaryNumber::TrinaryNumber(int value) : value_(value) {}

bool TrinaryNumber::IsLogical() const {
    if (value_ >= -1 && value_ <= 1) {
        return true;
    } else {
        throw notLogicalError(GetTrinary());
        return false;
    }
}

std::string TrinaryNumber::GetTrinary() const {
    std::string s;
    int temp_val;
    if (value_ >= 0) {
        temp_val = value_;
    } else {
        temp_val = -value_;
    }
    while (temp_val > 2) {
        int remainder = temp_val % 3;
        temp_val /= 3;
        if (remainder == 2) {
            s = "-" + s;
            temp_val++;
        } else if (remainder == 1) {
            s = "+" + s;
        } else {
            s = "0" + s;
        }        
    }
    if (temp_val == 2) {
        s = "+-" + s;
    } else if (temp_val == 1) {
        s = "+" + s;
    } else {
        s = "0" + s;
    }
    if (value_ < 0) {
        for (int iterator = 0; iterator < static_cast<int>(s.size()); ++iterator) {
            if (s[iterator] == '+') {
                s[iterator] = '-';
            } else if (s[iterator] == '-') {
                s[iterator] = '+';
            }
        }
    }
    return s;
}


TrinaryNumber operator+(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    return TrinaryNumber(lhs.value_ + rhs.value_);
}

TrinaryNumber operator-(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    return TrinaryNumber(lhs.value_ - rhs.value_);
}

TrinaryNumber operator*(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    return TrinaryNumber(lhs.value_ * rhs.value_);
}


TrinaryNumber operator&(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    if (lhs.IsLogical() && rhs.IsLogical()) {
        int min = lhs.value_;
        if (rhs.value_ < min) {
            min = rhs.value_;
        }
        return TrinaryNumber(min);
    }
    return TrinaryNumber(0);
}

TrinaryNumber operator|(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    if (lhs.IsLogical() && rhs.IsLogical()) {
        int max = lhs.value_;
        if (rhs.value_ > max) {
            max = rhs.value_;
        }
        return TrinaryNumber(max);
    }
    return TrinaryNumber(0);
}

TrinaryNumber operator~(const TrinaryNumber& operand)
{
    if (operand.IsLogical()) {        
        return TrinaryNumber(-operand.value_);
    }
    return TrinaryNumber(0);
}


TrinaryNumber operator==(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    if (lhs.value_ == rhs.value_) {
        return TrinaryNumber(1);
    }
    else {
        return TrinaryNumber(-1);
    }
}

TrinaryNumber operator!=(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    return ~(lhs == rhs);
}

TrinaryNumber operator<(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    if (lhs.value_ < rhs.value_) {
        return TrinaryNumber(1);
    }
    else {
        return TrinaryNumber(-1);
    }
}

TrinaryNumber operator>(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    if (lhs.value_ > rhs.value_) {
        return TrinaryNumber(1);
    }
    else {
        return TrinaryNumber(-1);
    }
}

TrinaryNumber operator<=(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    return ~(lhs > rhs);
}

TrinaryNumber operator>=(const TrinaryNumber& lhs, const TrinaryNumber& rhs)
{
    return ~(lhs < rhs);
}