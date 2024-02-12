#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Тестирование вычисления арктангенса из нуля
TEST(BigNumberArcTan, Zero) {
    BigNumber num("0", 3);
    BigNumber result = num.arctan();
    ASSERT_EQ("0.000", result.ToString());
}

// Тестирование вычисления арктангенса из положительного дробного числа
TEST(BigNumberArcTan, PositiveFractional) {
    BigNumber num("0.5", 10);
    BigNumber result = num.arctan();
// Используйте конкретное численное значение арктангенса 0.5, полученное из надежного источника
    ASSERT_NEAR(0.463647609, std::stod(result.ToString()), 1e-8);
}

