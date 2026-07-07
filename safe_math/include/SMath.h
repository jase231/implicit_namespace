#pragma once

#include "SResult.h"

// addition

auto safe_add(int a, int b) -> IntResult;

auto float_add(double a, double b) -> double;
auto float_add(int a, double b) -> double;
auto float_add(double a, int b) -> double;

auto add(int a, int b) -> IntResult;
auto add(double a, double b) -> DoubleResult;
auto add(int a, double b) -> DoubleResult;
auto add(double a, int b) -> DoubleResult;

// subtraction

auto safe_sub(int a, int b) -> IntResult;

auto float_sub(double a, double b) -> double;
auto float_sub(int a, double b) -> double;
auto float_sub(double a, int b) -> double;

auto sub(int a, int b) -> IntResult;
auto sub(double a, double b) -> DoubleResult;
auto sub(int a, double b) -> DoubleResult;
auto sub(double a, int b) -> DoubleResult;

// multiplication

auto safe_mul(int a, int b) -> IntResult;

auto float_mul(double a, double b) -> double;
auto float_mul(int a, double b) -> double;
auto float_mul(double a, int b) -> double;

auto mul(int a, int b) -> IntResult;
auto mul(double a, double b) -> DoubleResult;
auto mul(int a, double b) -> DoubleResult;
auto mul(double a, int b) -> DoubleResult;
