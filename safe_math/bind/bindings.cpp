#include <pybind11/pybind11.h>
#include <cstdint>
#include <stdexcept>

#include "SMath.h"

namespace py = pybind11;

// wrapper for treating std::expected as a python exception
template <typename T>
T unwrap(std::expected<T, std::string> res) {
    if (!res) {
	throw std::overflow_error(res.error());
    } else {
	return *res;
    }
}

// for mixed integral/float paramter pairs, pybind11 automatically chooses the float_* overload
PYBIND11_MODULE(safe_math, m) {
    m.doc() = "Bindings for the overflow-checked safe_math library";

    m.def("safe_add", [](int64_t a, int64_t b) { return unwrap(safe_add(a, b)); },
	py::arg("a"), py::arg("b"), "Overflow-checked integer addition");
    m.def("safe_add", [](double a, double b) { return float_add(a, b); }, 
	py::arg("a"), py::arg("b"), "Floating-point addition, can overflow to inf!");

    m.def("safe_sub", [](int64_t a, int64_t b) { return unwrap(safe_sub(a, b)); },
	py::arg("a"), py::arg("b"), "Overflow-checked integer subtraction");
    m.def("safe_sub", [](double a, double b) { return float_sub(a, b); }, 
	py::arg("a"), py::arg("b"), "Floating-point subtraction, can overflow to inf!");

    m.def("safe_mul", [](int64_t a, int64_t b) { return unwrap(safe_mul(a, b)); },
	py::arg("a"), py::arg("b"), "Overflow-checked integer multiplication");
    m.def("safe_mul", [](double a, double b) { return float_mul(a, b); }, 
	py::arg("a"), py::arg("b"), "Floating-point multiplication, can overflow to inf!");
}
