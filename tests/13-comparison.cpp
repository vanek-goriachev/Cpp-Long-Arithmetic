#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Тест для оператора равенства
TEST(BigNumberComparison, Equality) {
    BigNumber num1("123.45", 2);
    BigNumber num2("123.45", 2);
    BigNumber num3("123.46", 2);
    ASSERT_TRUE(num1 == num2);
    ASSERT_FALSE(num1 == num3);
}

// Тест для оператора неравенства
TEST(BigNumberComparison, Inequality) {
BigNumber num1("123.45", 2);
BigNumber num2("123.45", 2);
BigNumber num3("100", 2);
ASSERT_FALSE(num1 != num2);
ASSERT_TRUE(num1 != num3);
}

// Тест для оператора меньше
TEST(BigNumberComparison, LessThan) {
BigNumber num1("123.45", 2);
BigNumber num2("123.46", 2);
BigNumber num3("123.45", 2);
ASSERT_TRUE(num1 < num2);
ASSERT_FALSE(num2 < num1);
ASSERT_FALSE(num1 < num3);
}

// Тест для оператора больше
TEST(BigNumberComparison, GreaterThan) {
BigNumber num1("123.45", 2);
BigNumber num2("123", 0);
ASSERT_TRUE(num1 > num2);
ASSERT_FALSE(num2 > num1);
}

// Тест для оператора меньше или равно
TEST(BigNumberComparison, LessThanOrEqual) {
BigNumber num1("123.45", 2);
BigNumber num2("123.45", 2);
BigNumber num3("123", 0);
ASSERT_TRUE(num1 <= num2);
ASSERT_TRUE(num3 <= num1);
ASSERT_FALSE(num1 <= num3);
}

// Тест для оператора больше или равно
TEST(BigNumberComparison, GreaterThanOrEqual) {
BigNumber num1("123.45", 2);
BigNumber num2("123.45", 2);
BigNumber num3("124", 0);
ASSERT_TRUE(num1 >= num2);
ASSERT_TRUE(num3 >= num1);
ASSERT_FALSE(num1 >= num3);
}
