#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Проверка на корректность представления положительного числа
TEST(BigNumberToStringTest, HandlesPositiveNumber) {
    BigNumber number("123.456", 3);
    ASSERT_EQ("123.456", number.ToString());
}

// Проверка на корректность представления отрицательного числа
TEST(BigNumberToStringTest, HandlesNegativeNumber) {
    BigNumber number("-123.456", 3);
    ASSERT_EQ("-123.456", number.ToString());
}

// Проверка на корректное представление числа с нулевой дробной частью
TEST(BigNumberToStringTest, HandlesZeroDecimalPart) {
    BigNumber number("123", 2); // Точность 2, но дробной части нет
    ASSERT_EQ("123.00", number.ToString());
}

// Проверка представления числа без дробной части и точности
TEST(BigNumberToStringTest, HandlesIntegerWithoutPrecision) {
    BigNumber number("987654321", 0); // Без дробной части
    ASSERT_EQ("987654321", number.ToString());
}

// Проверка на представление нуля с заданной точностью
TEST(BigNumberToStringTest, HandlesZeroWithPrecision) {
    BigNumber number("0", 4);
    ASSERT_EQ("0.0000", number.ToString());
}