#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Тестирование увеличения точности числа
TEST(BigNumberChangePrecision, IncreasePrecision) {
    BigNumber num("123.45", 2);
    num.change_precision(4);
    ASSERT_EQ("123.4500", num.ToString());
}

TEST(BigNumberChangePrecision, DecreasePrecisionFloor) {
    BigNumber num("123.4567", 4);
    num.change_precision(2);
    ASSERT_EQ("123.45", num.ToString());
}

// Тестирование изменения точности на нулевую
TEST(BigNumberChangePrecision, ZeroPrecision) {
    BigNumber num("123.456", 3);
    num.change_precision(0);
    ASSERT_EQ("123", num.ToString()); // Ожидается удаление дробной части
}
