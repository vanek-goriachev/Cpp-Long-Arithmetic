#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Тестирование вычисления абсолютного значения для положительного числа
TEST(BigNumberAbs, PositiveNumber) {
    BigNumber num("123.45", 2);
    BigNumber result = num.abs();
    ASSERT_EQ("123.45", result.ToString());
}

// Тестирование вычисления абсолютного значения для отрицательного числа
TEST(BigNumberAbs, NegativeNumber) {
    BigNumber num("-123.45", 2);
    BigNumber result = num.abs();
    ASSERT_EQ("123.45", result.ToString());
}

// Тестирование вычисления абсолютного значения для нуля
TEST(BigNumberAbs, Zero) {
    BigNumber num("0", 0);
    BigNumber result = num.abs();
    ASSERT_EQ("0", result.ToString());
}

// Тестирование вычисления абсолютного значения для очень большого числа
TEST(BigNumberAbs, LargeNumber) {
    BigNumber num("-999999999999.999", 3);
    BigNumber result = num.abs();
    ASSERT_EQ("999999999999.999", result.ToString());
}

// Тестирование вычисления абсолютного значения для очень маленького положительного числа
TEST(BigNumberAbs, SmallPositiveNumber) {
    BigNumber num("0.0001", 4);
    BigNumber result = num.abs();
    ASSERT_EQ("0.0001", result.ToString());
}

// Тестирование вычисления абсолютного значения для очень маленького отрицательного числа
TEST(BigNumberAbs, SmallNegativeNumber) {
    BigNumber num("-0.0001", 4);
    BigNumber result = num.abs();
    ASSERT_EQ("0.0001", result.ToString());
}
