#include "SMath.h"

// addition

auto safe_add(int a, int b) -> IntResult {
    int res{};
    if (__builtin_add_overflow(a, b, &res)) {
        return { false, 0,
            "Error: Integer Overflow, cannot store result of a + b in a variable of type int" };
    } else {
        return { true, res, "" };
    }
}

auto float_add(double a, double b) -> double {
    return a + b;
}

auto float_add(int a, double b) -> double {
    return a + b;
}

auto float_add(double a, int b) -> double {
    return a + b;
}

auto add(int a, int b) -> IntResult {
    return safe_add(a, b);
}

auto add(double a, double b) -> DoubleResult {
    return { true, float_add(a, b), "" };
}

auto add(int a, double b) -> DoubleResult {
    return { true, float_add(a, b), "" };
}

auto add(double a, int b) -> DoubleResult {
    return { true, float_add(a, b), "" };
}

// subtraction

auto safe_sub(int a, int b) -> IntResult {
    int res{};
    if (__builtin_sub_overflow(a, b, &res)) {
        return { false, 0,
            "Error: Integer Overflow, cannot store result of a - b in a variable of type int" };
    } else {
        return { true, res, "" };
    }
}

auto float_sub(double a, double b) -> double {
    return a - b;
}

auto float_sub(int a, double b) -> double {
    return a - b;
}

auto float_sub(double a, int b) -> double {
    return a - b;
}

auto sub(int a, int b) -> IntResult {
    return safe_sub(a, b);
}

auto sub(double a, double b) -> DoubleResult {
    return { true, float_sub(a, b), "" };
}

auto sub(int a, double b) -> DoubleResult {
    return { true, float_sub(a, b), "" };
}

auto sub(double a, int b) -> DoubleResult {
    return { true, float_sub(a, b), "" };
}

// multiplication

auto safe_mul(int a, int b) -> IntResult {
    int res{};
    if (__builtin_mul_overflow(a, b, &res)) {
        return { false, 0,
            "Error: Integer Overflow, cannot store result of a * b in a variable of type int" };
    } else {
        return { true, res, "" };
    }
}

auto float_mul(double a, double b) -> double {
    return a * b;
}

auto float_mul(int a, double b) -> double {
    return a * b;
}

auto float_mul(double a, int b) -> double {
    return a * b;
}

auto mul(int a, int b) -> IntResult {
    return safe_mul(a, b);
}

auto mul(double a, double b) -> DoubleResult {
    return { true, float_mul(a, b), "" };
}

auto mul(int a, double b) -> DoubleResult {
    return { true, float_mul(a, b), "" };
}

auto mul(double a, int b) -> DoubleResult {
    return { true, float_mul(a, b), "" };
}
