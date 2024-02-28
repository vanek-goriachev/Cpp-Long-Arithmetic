ПРОЕКТ Cpp-Long-Arithmetic

Проект реализован в рамках курса "Алгоритмы и алгоритмические языки", который проходится на первом курсе Образовательной программы "Программная инженерия" в Высшей Школе Экономики.
В проекте реализована библиотека для работы с длинной арифметикой (дробные числа с заранее заданной точностью)
Для демонстрации возможностей библиотеки написан внешний скрипт, который с использованием средств библиотеки вычисляет число ПИ с заданной точностью и выводит время затраченной на вычисления.


Run project on Mac: 
    build: cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    
    For run anything first of all do: cd build
    build tests: cmake --build . --target tests
    run tests: ./tests/tests

    build and run runnn: cmake --build . --target runnn
    to run it again: ./CppLongAriphmetic
