#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Группа тестов для проверки конструктора из float
TEST(BigNumberConstructor, FromFloat) {
    // Тест с положительным числом
    BigNumber positiveNumber(123.456f, 3);
    ASSERT_EQ("123.456", positiveNumber.ToString());

    // Тест с отрицательным числом
    BigNumber negativeNumber(-123.456f, 3);
    ASSERT_EQ("-123.456", negativeNumber.ToString());

    // Тест с нулем
    BigNumber zeroNumber(0.0f, 2);
    ASSERT_EQ("0.00", zeroNumber.ToString());

    // Тест с очень маленьким числом
    BigNumber smallNumber(0.0001234f, 6);
    ASSERT_EQ("0.000123", smallNumber.ToString());

    // Тест с округлением вверх
    BigNumber roundUpNumber(123.4567f, 3);
    ASSERT_EQ("123.457", roundUpNumber.ToString());

    // Тест с округлением вниз
    BigNumber roundDownNumber(123.4561f, 3);
    ASSERT_EQ("123.456", roundDownNumber.ToString());
}
