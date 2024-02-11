#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Тестирование вычисления квадратного корня из положительного числа
TEST(BigNumberSqrt, PositiveNumber) {
    BigNumber num("4", 0);
    BigNumber result = num.sqrt();
    ASSERT_EQ("2", result.ToString());
}

// Тестирование вычисления квадратного корня из нуля
TEST(BigNumberSqrt, Zero) {
    BigNumber num("0", 0);
    BigNumber result = num.sqrt();
    ASSERT_EQ("0", result.ToString());
}

// Тестирование вычисления квадратного корня из единицы
TEST(BigNumberSqrt, One) {
    BigNumber num("1", 0);
    BigNumber result = num.sqrt();
    ASSERT_EQ("1", result.ToString());
}
