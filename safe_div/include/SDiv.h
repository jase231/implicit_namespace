#pragma once

#include "SResult.h"

auto safe_div(int a, int b) -> IntResult;

auto float_div(double a, double b) -> DoubleResult;
auto float_div(int a, double b) -> DoubleResult;
auto float_div(double a, int b) -> DoubleResult;

auto divide(int a, int b) -> IntResult;
auto divide(double a, double b) -> DoubleResult;
auto divide(int a, double b) -> DoubleResult;
auto divide(double a, int b) -> DoubleResult;
