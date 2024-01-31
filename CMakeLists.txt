cmake_minimum_required(VERSION 3.26)  # Указание минимальной версии CMake

# Имя проекта и указание используемого языка программирования.
project(CppLongAriphmetic)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 14)

# Создание исполняемого файла из указанных исходных файлов.
add_executable(${PROJECT_NAME} main.cpp
        LongArithmetic.cpp)

# Включение директорий
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}")
