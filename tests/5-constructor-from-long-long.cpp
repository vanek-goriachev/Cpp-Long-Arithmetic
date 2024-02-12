#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

TEST(BigNumberConstructor, FromLongLong) {
    // Тест с положительным числом без дробной части
    BigNumber positiveNumber(123456789LL, 0);
    ASSERT_EQ("123456789", positiveNumber.ToString());

    // Тест с отрицательным числом и точностью до двух знаков после запятой
    BigNumber negativeNumber(-123456789LL, 2);
    ASSERT_EQ("-123456789.00", negativeNumber.ToString());

    // Тест с нулем и разной точностью
    BigNumber zeroNumber(0LL, 4);
    ASSERT_EQ("0.0000", zeroNumber.ToString());

    BigNumber zeroNumberDifferentPrecision(0LL, 6);
    ASSERT_EQ("0.000000", zeroNumberDifferentPrecision.ToString());

    // Тест с большим числом и точностью
    BigNumber largeNumber(9223372036854775807LL, 5); // Максимальное значение для long long
    ASSERT_EQ("9223372036854775807.00000", largeNumber.ToString());

    // Тест с точностью равной 0 для положительного числа
    BigNumber precisePositiveNumber(12345LL, 0);
    ASSERT_EQ("12345", precisePositiveNumber.ToString());

    // Тест с точностью равной 0 для отрицательного числа
    BigNumber preciseNegativeNumber(-12345LL, 0);
    ASSERT_EQ("-12345", preciseNegativeNumber.ToString());
}
