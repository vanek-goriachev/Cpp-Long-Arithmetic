
#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Группа тестов для проверки конструктора из string
TEST(BigNumberConstructor, FromStringWithPrecision) {
    // Проверка инициализации с положительным числом
    BigNumber positiveNumber("123.45", 2);
    ASSERT_EQ(positiveNumber.ToString(), "123.45");

    // Проверка инициализации с отрицательным числом
    BigNumber negativeNumber("-123.45", 2);
    ASSERT_EQ(negativeNumber.ToString(), "-123.45");

    // Проверка инициализации с нулем
    BigNumber zeroNumber("0", 2);
    ASSERT_EQ(zeroNumber.ToString(), "0.00");

    // Проверка инициализации с точностью больше, чем в исходной строке
    BigNumber highPrecisionNumber("123.456", 5);
    ASSERT_EQ(highPrecisionNumber.ToString(), "123.45600");

    // Проверка инициализации с точностью меньше, чем в исходной строке
    BigNumber lowPrecisionNumber("123.4567890", 3);
    ASSERT_EQ(lowPrecisionNumber.ToString(), "123.456");

    // Проверка инициализации без десятичной части
    BigNumber integerOnly("1234", 2);
    ASSERT_EQ(integerOnly.ToString(), "1234.00");
}
