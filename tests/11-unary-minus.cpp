#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Проверка изменения знака положительного числа
TEST(BigNumberUnaryMinus, PositiveToNegative) {
    BigNumber positiveNumber("123.45", 2);
    BigNumber result = -positiveNumber;
    ASSERT_EQ("-123.45", result.ToString());
}

// Проверка изменения знака отрицательного числа
TEST(BigNumberUnaryMinus, NegativeToPositive) {
    BigNumber negativeNumber("-123.45", 2);
    BigNumber result = -negativeNumber;
    ASSERT_EQ("123.45", result.ToString());
}

// Проверка изменения знака числа с нулевым значением
TEST(BigNumberUnaryMinus, ZeroRemainsUnchanged) {
    BigNumber zero("0", 0);
    BigNumber result = -zero;
    ASSERT_EQ("0", result.ToString()); // Проверяем, что нуль остается нулем, поскольку (-0) и 0 эквивалентны.
}

// Проверка изменения знака очень большого числа
TEST(BigNumberUnaryMinus, LargeNumber) {
    BigNumber largeNumber("999999999999999999.999", 3);
    BigNumber result = -largeNumber;
    ASSERT_EQ("-999999999999999999.999", result.ToString()); // Проверка на очень большое число
}

// Проверка изменения знака очень маленького числа
TEST(BigNumberUnaryMinus, SmallNumber) {
    BigNumber smallNumber("0.0000000000001", 13);
    BigNumber result = -smallNumber;
    ASSERT_EQ("-0.0000000000001", result.ToString()); // Проверка на очень маленькое число
}