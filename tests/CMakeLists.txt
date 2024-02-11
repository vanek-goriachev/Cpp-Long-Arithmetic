cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(tests)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests very_good_test.cpp)
target_include_directories(tests PUBLIC ../)
target_link_libraries(tests mylib gtest gtest_main)
