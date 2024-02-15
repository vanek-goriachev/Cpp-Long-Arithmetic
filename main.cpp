//
// Created by Vanek on 01.02.2024.
//
#include "iostream"
#include "my-library/LongArithmetic.hpp"
#include <ctime>

using namespace std;

BigNumber clock_decorator(int precision, BigNumber func(int)) {
    clock_t start = clock();

    BigNumber result = func(precision);

    clock_t end = clock();
    double seconds = (double) (end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);

    return result;
}

BigNumber calculate_pi(int precision) {
    precision += 10;
    BigNumber one("1", precision), two("2", precision),
            three("3", precision), four("4", precision);

    BigNumber Pi1 = four * ((one / two).arctan() + (one / three).arctan());
    Pi1.change_precision(precision - 10);


    return Pi1;
}

int main(int argc, char *argv[]) {
    int precision;
    cout << "Введите требуемое количество знаков после запятой";
    cin >> precision;
    BigNumber magicNumber = clock_decorator(precision, calculate_pi);
    cout << magicNumber.ToString() << endl;
    return 0;
}
