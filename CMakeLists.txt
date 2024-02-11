# cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_MAKE_PROGRAM="C:/Program Files (x86)/GnuWin32/bin/make.exe" -DCMAKE_CXX_COMPILER="C:/MinGW/bin/g++.exe" -DCMAKE_BUILD_TYPE=Release
cmake_minimum_required(VERSION 3.24)  # Указание минимальной версии CMake

# Имя проекта и указание используемого языка программирования.
project(CppLongAriphmetic  LANGUAGES CXX)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление библиотеки
add_library(LongArithmetic SHARED
        LongArithmetic.hpp
        LongArithmetic.cpp
        )

# Создание исполняемого файла из указанных исходных файлов.
add_executable(${PROJECT_NAME} main.cpp)

# Подключения библиотеки к файлу
target_link_libraries(${PROJECT_NAME} LongArithmetic)

# Создание цели для запуска исполняемого файла
# Теперь можно писать make run для запуска проги
add_custom_target(run COMMAND ${PROJECT_NAME})

## Создание исполняемого файла с тестами
#add_executable(tests tests.cpp)
#
## Подключения библиотеки к файлу с тестами
#target_link_libraries(tests LongArithmetic)
#
## Создание цели для запуска исполняемого файла с тестами
## Теперь можно писать make test для запуска тестов
#add_custom_target(test COMMAND tests)