#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Проверка деления двух положительных чисел
TEST(BigNumberDivision, DividePositiveNumbers) {
    BigNumber num1("100", 0);
    BigNumber num2("20", 0);
    BigNumber result = num1 / num2;
    ASSERT_EQ("5", result.ToString());
}

// Проверка деления на единицу
TEST(BigNumberDivision, DivideByOne) {
    BigNumber num1("123.45", 2);
    BigNumber one("1", 0);
    BigNumber result = num1 / one;
    ASSERT_EQ("123.45", result.ToString());
}

// Проверка деления отрицательного на положительное число и наоборот
TEST(BigNumberDivision, DivideNegativeByPositive) {
    BigNumber num1("-100", 0);
    BigNumber num2("25", 0);
    BigNumber result = num1 / num2;
    ASSERT_EQ("-4", result.ToString());

    BigNumber num3("100", 0);
    BigNumber num4("-25", 0);
    result = num3 / num4;
    ASSERT_EQ("-4", result.ToString());
}

// Проверка деления двух отрицательных чисел
TEST(BigNumberDivision, DivideNegativeNumbers) {
    BigNumber num1("-100", 0);
    BigNumber num2("-20", 0);
    BigNumber result = num1 / num2;
    ASSERT_EQ("5", result.ToString());
}

// Проверка деления с нулём в качестве делимого
TEST(BigNumberDivision, DivideZeroByNumber) {
    BigNumber zero("0", 0);
    BigNumber num1("123.45", 2);
    BigNumber result = zero / num1;
    ASSERT_EQ("0", result.ToString());
}


// Попытка деления на ноль должна всегда предусматривать безопасное поведение. Реализация этого теста зависит от вашего дизайна.
TEST(BigNumberDivision, DivideByZero) {
    BigNumber num1("100", 0);
    BigNumber zero("0", 0);
    ASSERT_THROW({
                     try {
                         BigNumber result = num1 / zero;
                     } catch (const std::invalid_argument &e) {
                         // Переброс исключения для его перехвата фреймворком тестирования
                         throw;
                     }
                 }, std::invalid_argument);
}
