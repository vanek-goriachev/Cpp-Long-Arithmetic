cmake_minimum_required(VERSION 3.24)

# Имя проекта и указание используемого языка программирования.
project(CppLongAriphmetic  LANGUAGES CXX)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(my-library)
add_subdirectory(tests)

target_link_libraries(${PROJECT_NAME} mylib)

add_custom_target(run COMMAND ${PROJECT_NAME})
