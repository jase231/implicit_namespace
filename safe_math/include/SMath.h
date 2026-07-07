#pragma once

#include <concepts>
#include <expected>
#include <string>

// matches when A and B will produce a float / value promoted to float
template <typename A, typename B>
concept promotes_to_float = std::floating_point<A> or
			    std::floating_point<B>;

// constrains the inputs to promotes_to_float further by catching non-numeric types with operator+
template <typename T>
concept numeric = std::integral<T> or std::floating_point<T>;

// addition

auto safe_add(std::integral auto a, std::integral auto b) -> std::expected<decltype(a + b), std::string> {
    decltype(a + b) res{};
    if (__builtin_add_overflow(a, b, &res)) {
	return std::unexpected{ "Error: Integer Overflow, cannot store result of a + b in a variable of type decltype(a + b)" };
    } else {
	return res;
    }
}
 
auto float_add(numeric auto a, numeric auto b) -> decltype(a + b)
requires promotes_to_float<decltype(a), decltype(b)> {
    return a + b;
}
 
auto add(numeric auto a, numeric auto b) -> std::expected<decltype(a + b), std::string> {
    if constexpr (promotes_to_float<decltype(a), decltype(b)>) {
	return float_add(a, b);
    } else {
	return safe_add(a, b);
    }
}

// subtraction

auto safe_sub(std::integral auto a, std::integral auto b) -> std::expected<decltype(a - b), std::string> {
    decltype(a - b) res{};
    if (__builtin_sub_overflow(a, b, &res)) {
	return std::unexpected{ "Error: Integer Overflow, cannot store result of a - b in a variable of type decltype(a - b)" };
    } else {
	return res;
    }
}
 
auto float_sub(numeric auto a, numeric auto b) -> decltype(a - b)
requires promotes_to_float<decltype(a), decltype(b)> {
    return a - b;
}
 
auto sub(numeric auto a, numeric auto b) -> std::expected<decltype(a - b), std::string> {
    if constexpr (promotes_to_float<decltype(a), decltype(b)>) {
	return float_sub(a, b);
    } else {
	return safe_sub(a, b);
    }
}

// multiplicatoin

auto safe_mul(std::integral auto a, std::integral auto b) -> std::expected<decltype(a * b), std::string> {
    decltype(a * b) res{};
    if (__builtin_mul_overflow(a, b, &res)) {
	return std::unexpected{ "Error: Integer Overflow, cannot store result of a * b in a variable of type decltype(a * b)" };
    } else {
	return res;
    }
}

auto float_mul(numeric auto a, numeric auto b) -> decltype(a * b)
requires promotes_to_float<decltype(a), decltype(b)> {
    return a * b;
}

auto mul(numeric auto a, numeric auto b) -> std::expected<decltype(a * b), std::string> {
    if constexpr (promotes_to_float<decltype(a), decltype(b)>) {
	return float_mul(a, b);
    } else {
	return safe_mul(a, b);
    }
}
