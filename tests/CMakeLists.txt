cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(tests)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests run_tests.cpp 1-copy-test.cpp 2-constructor-from-string.cpp 3-constructor-from-float.cpp 4-constructor-from-double.cpp 5-constructor-from-long-long.cpp 6-to-string-method.cpp 7-plus-operator.cpp 8-minus-operator.cpp 9-multiply-operator.cpp 10-divide-operator.cpp 11-unary-minus.cpp 12-equals.cpp 13-comparison.cpp 14-power.cpp 15-sqrt.cpp 16-arctan.cpp 17-abs.cpp 18-change-precision.cpp)
target_include_directories(tests PUBLIC ../)
target_link_libraries(tests mylib gtest gtest_main)
