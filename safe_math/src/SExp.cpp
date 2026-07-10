#include "SExp.h"

#include <string_view>

constexpr const char* IntOverflowMsg =
    "Error: Integer Overflow, cannot store result of base ^ exponent in a variable of type int";
constexpr const char* NegExpZeroBaseMsg =
    "Error: Undefined, 0 raised to a negative exponent is undefined";
constexpr const char* NegExpNonIntMsg =
    "Error: Negative exponent, result of base ^ exponent is not representable as int";

auto safe_expo(int base, int exponent) -> IntResult {
    // Negative exponents: result is 1 / base^|exponent|, only an integer in
    // the special cases below.
    if (exponent < 0) {
        if (base == 0) {
            return { false, 0, NegExpZeroBaseMsg };
        }
        if (base == 1) {
            return { true, 1, "" };
        }
        if (base == -1) {
            return { true, (exponent % 2 == 0) ? 1 : -1, "" };
        }
        return { false, 0, NegExpNonIntMsg };
    }
 
    // exponentiation by squaring, overflow detected by safe_mul/mul
    int result = 1;   // base ^ 0
    int b = base;
    int e = exponent;
 
    while (e > 0) {
        if (e & 1) {
            IntResult r = mul(result, b);          // result *= b
            if (!r.ok) {
                return { false, 0, IntOverflowMsg };
            }
            result = r.value;
        }
 
        e >>= 1;
        if (e > 0) {                                // avoid a needless final square
            IntResult r = mul(b, b);               // b *= b
            if (!r.ok) {
                return { false, 0, IntOverflowMsg };
            }
            b = r.value;
        }
    }
 
    return { true, result, "" };
}
 
auto expo(int base, int exponent) -> IntResult {
    return safe_expo(base, exponent);
}
 
auto safe_expo(double base, int exponent) -> DoubleResult {
    bool negative = exponent < 0;
 
    unsigned int e = negative
        ? static_cast<unsigned int>(-(static_cast<long long>(exponent)))
        : static_cast<unsigned int>(exponent);
 
    double result = 1.0;   // base ^ 0
    double b = base;
 
    while (e > 0) {
        if (e & 1u) {
            result = mul(result, b).value;   // float multiply via base library
        }
        e >>= 1;
        if (e > 0) {
            b = mul(b, b).value;
        }
    }
 
    if (negative) {
        result = 1.0 / result;
    }
 
    return { true, result, "" };
}
 
auto expo(double base, int exponent) -> DoubleResult {
    return safe_expo(base, exponent);
}
 
