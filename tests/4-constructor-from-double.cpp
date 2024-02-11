#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Группа тестов для проверки конструктора из double
TEST(BigNumberConstructor, FromDouble) {
    // Тест с положительным числом и точностью до трех знаков после запятой
    BigNumber positiveNumber(123.45678, 3);
    ASSERT_EQ("123.457", positiveNumber.ToString());

    // Тест с отрицательным числом
    BigNumber negativeNumber(-123.45678, 3);
    ASSERT_EQ("-123.457", negativeNumber.ToString());

    // Тест с нулем и разной точностью
    BigNumber zeroNumber(0.0, 2);
    ASSERT_EQ("0.00", zeroNumber.ToString());

    BigNumber zeroNumberHighPrecision(0.0, 5);
    ASSERT_EQ("0.00000", zeroNumberHighPrecision.ToString());

    // Тест с округлением вверх
    BigNumber roundUpNumber(123.456789, 5);
    ASSERT_EQ("123.45679", roundUpNumber.ToString());

    // Тест с округлением вниз
    BigNumber roundDownNumber(123.456781, 5);
    ASSERT_EQ("123.45678", roundDownNumber.ToString());

    // Тест с очень маленьким числом
    BigNumber verySmallNumber(0.000123456, 7);
    ASSERT_EQ("0.0001235", verySmallNumber.ToString());

    // Тест на точность с очень малым изменением
    BigNumber preciseNumber(12345.00001, 5);
    ASSERT_EQ("12345.00001", preciseNumber.ToString());
}
