#pragma once

#include <string>

struct IntResult {
    bool ok;
    int value;
    std::string error;
};

struct DoubleResult {
    bool ok;
    double value;
    std::string error;
};
