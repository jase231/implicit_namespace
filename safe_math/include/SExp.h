#pragma once

#include "SMath.h"

auto safe_expo(int base, int exponent) -> IntResult;
auto expo(int base, int exponent) -> IntResult;
auto safe_expo(double base, int exponent) -> DoubleResult;
auto expo(double base, int exponent) -> DoubleResult;
