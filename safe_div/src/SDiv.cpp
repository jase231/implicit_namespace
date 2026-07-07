#include "SDiv.h"

auto safe_div(int a, int b) -> IntResult {
    if (b == 0) {
        return { false, 0,
            "Error: Division by Zero, cannot divide a by b when b is 0" };
    } else {
        return { true, a / b, "" };
    }
}

auto float_div(double a, double b) -> DoubleResult {
    if (b == 0.0) {
        return { false, 0.0,
            "Error: Division by Zero, cannot divide a by b when b is 0" };
    } else {
        return { true, a / b, "" };
    }
}

auto float_div(int a, double b) -> DoubleResult {
    if (b == 0.0) {
        return { false, 0.0,
            "Error: Division by Zero, cannot divide a by b when b is 0" };
    } else {
        return { true, a / b, "" };
    }
}

auto float_div(double a, int b) -> DoubleResult {
    if (b == 0) {
        return { false, 0.0,
            "Error: Division by Zero, cannot divide a by b when b is 0" };
    } else {
        return { true, a / b, "" };
    }
}

auto divide(int a, int b) -> IntResult {
    return safe_div(a, b);
}

auto divide(double a, double b) -> DoubleResult {
    return float_div(a, b);
}

auto divide(int a, double b) -> DoubleResult {
    return float_div(a, b);
}

auto divide(double a, int b) -> DoubleResult {
    return float_div(a, b);
}
