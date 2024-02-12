#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Проверка вычитания двух положительных чисел
TEST(BigNumberSubtractionTest, SubtractPositiveNumbers) {
    BigNumber num1("500.00", 2);
    BigNumber num2("300.00", 2);
    BigNumber result = num1 - num2;
    ASSERT_EQ("200.00", result.ToString());
}

// Проверка вычитания положительного числа из отрицательного
TEST(BigNumberSubtractionTest, SubtractPositiveFromNegative) {
    BigNumber num1("-500", 0);
    BigNumber num2("200", 0);
    BigNumber result = num1 - num2;
    ASSERT_EQ("-700", result.ToString());
}

// Проверка вычитания двух отрицательных чисел
TEST(BigNumberSubtractionTest, SubtractNegativeNumbers) {
    BigNumber num1("-100", 0);
    BigNumber num2("-300", 0);
    BigNumber result = num1 - num2;
    ASSERT_EQ("200", result.ToString()); // Возможно неочевидное поведение, зависит от реализации
}

// Проверка вычитания из нуля
TEST(BigNumberSubtractionTest, SubtractFromZero) {
    BigNumber num1("0", 2);
    BigNumber num2("123.45", 2);
    BigNumber result = num1 - num2;
    ASSERT_EQ("-123.45", result.ToString());
}

// Проверка вычитания с нулем
TEST(BigNumberSubtractionTest, SubtractWithZero) {
    BigNumber num1("123.45", 2);
    BigNumber zero("0", 2);
    BigNumber result = num1 - zero;
    ASSERT_EQ("123.45", result.ToString());
}

// Проверка вычитания числа самого из себя
TEST(BigNumberSubtractionTest, SubtractItself) {
    BigNumber num("123.45", 2);
    BigNumber result = num - num;
    ASSERT_EQ("0.00", result.ToString());
}

// Проверка вычитания чисел с разной точностью
TEST(BigNumberSubtractionTest, SubtractNumbersDifferentPrecision) {
    BigNumber num1("123.4567", 4);
    BigNumber num2("23.0000", 4);
    BigNumber result = num1 - num2;
    ASSERT_EQ("100.4567", result.ToString());
}
