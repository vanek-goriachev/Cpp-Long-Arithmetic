#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Тестирование возведения в положительную степень
TEST(BigNumberPower, PositiveExponent) {
    BigNumber num("2", 0);
    BigNumber result = num.power(3);
    ASSERT_EQ("8", result.ToString());
}

// Тестирование возведения в степень ноль
TEST(BigNumberPower, ZeroExponent) {
    BigNumber num("123.45", 2);
    BigNumber result = num.power(0);
    ASSERT_EQ("1.00", result.ToString()); // Возведение любого числа в степень 0 равно 1
}

// Тестирование возведения нуля в положительную степень
TEST(BigNumberPower, ZeroBasePositiveExponent) {
    BigNumber num("0", 0);
    BigNumber result = num.power(3);
    ASSERT_EQ("0", result.ToString()); // Ноль в любой положительной степени равен нулю
}

// Тестирование возведения нуля в нулевую степень
TEST(BigNumberPower, ZeroBaseZeroExponent) {
    BigNumber num("0", 0);
    BigNumber result = num.power(0);
    // Здесь ожидаемое поведение может зависеть от реализации, мы предполагаем возвращение 1 для совместимости
    ASSERT_EQ("1", result.ToString());
}

// Тестирование возведения отрицательного числа в положительную четную степень
TEST(BigNumberPower, NegativeBasePositiveEvenExponent) {
    BigNumber num("-2", 0);
    BigNumber result = num.power(2);
    ASSERT_EQ("4", result.ToString());
}

// Тестирование возведения отрицательного числа в положительную нечетную степень
TEST(BigNumberPower, NegativeBasePositiveOddExponent) {
    BigNumber num("-2", 0);
    BigNumber result = num.power(3);
    ASSERT_EQ("-8", result.ToString());
}

// Тестирование возведения дробного числа в положительную степень
TEST(BigNumberPower, FractionalBasePositiveExponent) {
    BigNumber num("0.5", 2);
    BigNumber result = num.power(2);
    ASSERT_EQ("0.25", result.ToString());
}

// Тестирование возведения дробного отрицательного числа в степень
TEST(BigNumberPower, NegativeFractionalBasePositiveEvenExponent) {
    BigNumber num("-0.5", 2);
    BigNumber result = num.power(2);
    ASSERT_EQ("0.25", result.ToString());
}

TEST(BigNumberPower, NegativeFractionalBasePositiveOddExponent) {
    BigNumber num("-0.5", 3);
    BigNumber result = num.power(3);
    ASSERT_EQ("-0.125", result.ToString());
}