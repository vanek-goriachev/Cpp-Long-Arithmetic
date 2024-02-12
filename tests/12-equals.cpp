#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Тест для оператора присваивания
TEST(BigNumberOperators, Assignment) {
    BigNumber num1("123.45", 2);
    BigNumber num2 = num1;
    ASSERT_EQ(num2.ToString(), "123.45");
}

// Тест для оператора сложения и присваивания с BigNumber
TEST(BigNumberOperators, PlusEqualsBigNumber) {
    BigNumber num("100", 0);
    num += BigNumber("50", 0);
    ASSERT_EQ(num.ToString(), "150");
}

// Тест для оператора вычитания и присваивания с BigNumber
TEST(BigNumberOperators, MinusEqualsBigNumber) {
    BigNumber num("100", 0);
    num -= BigNumber("50", 0);
    ASSERT_EQ(num.ToString(), "50");
}

// Тест для оператора умножения и присваивания с BigNumber
TEST(BigNumberOperators, MultiplyEqualsBigNumber) {
    BigNumber num("10", 0);
    num *= BigNumber("5", 0);
    ASSERT_EQ(num.ToString(), "50");
}

// Тест для оператора деления и присваивания с BigNumber
TEST(BigNumberOperators, DivideEqualsBigNumber) {
    BigNumber num("100", 0);
    num /= BigNumber("50", 0);
    ASSERT_EQ(num.ToString(), "2");
}

// Тест для оператора сложения и присваивания с long long
TEST(BigNumberOperators, PlusEqualsLongLong) {
    BigNumber num("100", 0);
    num += 50LL;
    ASSERT_EQ(num.ToString(), "150");
}

// Тест для оператора вычитания и присваивания с long long
TEST(BigNumberOperators, MinusEqualsLongLong) {
    BigNumber num("100", 0);
    num -= 50LL;
    ASSERT_EQ(num.ToString(), "50");
}

// Тест для оператора умножения и присваивания с long long
TEST(BigNumberOperators, MultiplyEqualsLongLong) {
    BigNumber num("10", 0);
    num *= 5LL;
    ASSERT_EQ(num.ToString(), "50");
}

// Тест для оператора деления и присваивания с long long
TEST(BigNumberOperators, DivideEqualsLongLong) {
    BigNumber num("100", 0);
    num /= 50LL;
    ASSERT_EQ(num.ToString(), "2");
}
