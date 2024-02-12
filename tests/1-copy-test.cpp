#include <gtest/gtest.h>
#include <my-library/LongArithmetic.hpp>

// Группа тестов для проверки конструктора копирования
TEST(BigNumberCopyConstructor, CopyConstructorCreatesIdenticalObject) {
    // Исходный объект для копирования
    BigNumber originalNumber("123.456", 3);

    // Создание копии с помощью конструктора копирования
    BigNumber copiedNumber(originalNumber);

    // Проверка, что содержимое копии идентично исходному объекту
    ASSERT_EQ(copiedNumber.ToString(), originalNumber.ToString());
}

TEST(BigNumberCopyConstructor, CopyIsIndependent) {
    // Исходный объект для копирования
    BigNumber originalNumber("123.456", 3);

    // Создание копии
    BigNumber copiedNumber(originalNumber);

    // Изменение исходного объекта
    originalNumber = BigNumber("789.1011", 4);

    // Проверка, что изменение исходного объекта не повлияло на копию
    ASSERT_EQ(copiedNumber.ToString(), "123.456");
    ASSERT_EQ(originalNumber.ToString(), "789.1011");
}