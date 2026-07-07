cmake_minimum_required(VERSION 3.15)
project(safe_math LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python COMPONENTS Interpreter Development REQUIRED)
include(FetchContent)

FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v3.0.4   # pin to whatever version you want
)
FetchContent_MakeAvailable(pybind11)

add_library(SMath INTERFACE)
target_include_directories(SMath INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(SMath INTERFACE cxx_std_23)

pybind11_add_module(safe_math bind/bindings.cpp)
target_link_libraries(safe_math PRIVATE SMath)

# the .so counts as its own import package, so it sits at namespace root,
# not inside another dir the way a python package would
install(TARGETS safe_math DESTINATION .)

