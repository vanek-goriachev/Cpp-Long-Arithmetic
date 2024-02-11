#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Проверка сложения двух положительных чисел
TEST(BigNumberAdditionTest, AddPositiveNumbers) {
    BigNumber num1("123.45", 2);
    BigNumber num2("876.55", 2);
    BigNumber result = num1 + num2;
    ASSERT_EQ("1000.00", result.ToString());
}

// Проверка сложения положительного и отрицательного числа
TEST(BigNumberAdditionTest, AddPositiveAndNegativeNumber) {
    BigNumber num1("1000", 0);
    BigNumber num2("-500", 0);
    BigNumber result = num1 + num2;
    ASSERT_EQ("500", result.ToString());
}

// Проверка сложения двух отрицательных чисел
TEST(BigNumberAdditionTest, AddNegativeNumbers) {
    BigNumber num1("-100.50", 2);
    BigNumber num2("-200.50", 2);
    BigNumber result = num1 + num2;
    ASSERT_EQ("-301.00", result.ToString());
}

// Проверка сложения с нулем
TEST(BigNumberAdditionTest, AddWithZero) {
    BigNumber num1("12345.678", 3);
    BigNumber zero("0", 3);
    BigNumber result = num1 + zero;
    ASSERT_EQ("12345.678", result.ToString());
}
