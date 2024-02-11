#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Проверка умножения положительных чисел
TEST(BigNumberMultiplication, MultiplyPositiveNumbers) {
    BigNumber num1("12.3", 2);
    BigNumber num2("3.4", 2);
    BigNumber result = num1 * num2;
    ASSERT_EQ("41.82", result.ToString()); // Предполагаемая реализация ToString учитывает точность.
}

// Проверка умножения отрицательного на положительное число
TEST(BigNumberMultiplication, MultiplyNegativeByPositive) {
    BigNumber num1("-5.5", 1);
    BigNumber num2("4", 1);
    BigNumber result = num1 * num2;
    ASSERT_EQ("-22.0", result.ToString());
}

// Проверка умножения двух отрицательных чисел
TEST(BigNumberMultiplication, MultiplyNegativeNumbers) {
    BigNumber num1("-2", 0);
    BigNumber num2("-3", 0);
    BigNumber result = num1 * num2;
    ASSERT_EQ("6", result.ToString());
}

// Проверка умножения на ноль
TEST(BigNumberMultiplication, MultiplyByZero) {
    BigNumber num1("123.45", 2);
    BigNumber zero("0", 2);
    BigNumber result = num1 * zero;
    ASSERT_EQ("0.00", result.ToString()); // Проверка на ноль с точностью до двух знаков после запятой
}
