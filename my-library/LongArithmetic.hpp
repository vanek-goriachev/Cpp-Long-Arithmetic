//
// Created by Vanek on 01.02.2024.
//
#pragma once

#include "string"

class BigNumber
{
private:
    std::string integerPart;  // Целая часть числа
    std::string decimalPart;  // Десятичная часть числа (до заданной точности)
    bool negative;       // Флаг отрицательности числа
    size_t precision;    // Точность после запятой

    void normalize();

public:
    // Конструктор из BigNumber
    BigNumber(const BigNumber &other);

    // Конструктор из строки
    BigNumber(const std::string &number, size_t precision);

    // Конструктор из float
    BigNumber(float number, size_t prec);

    // Конструктор из double
    BigNumber(double number, size_t prec);

    // Конструктор из long long
    BigNumber(long long number, size_t prec);

    // Метод для получения строкового представления числа
    std::string ToString() const;

    // Перегрузка арифметических операторов
    BigNumber operator+(const BigNumber &other) const;

    BigNumber operator-(const BigNumber &other) const;

    BigNumber operator*(const BigNumber &other) const;

    BigNumber operator/(const BigNumber &other) const;

    // Перегрузка оператора унарный минус
    BigNumber operator-() const;

    BigNumber operator+(const long long &other);

    BigNumber operator-(const long long &other);

    BigNumber operator*(const long long &other);

    BigNumber operator/(const long long &other);

    // Перегрузка оператора присваивания
    BigNumber &operator=(const BigNumber &other);

    BigNumber operator+=(const BigNumber &other);

    BigNumber operator-=(const BigNumber &other);

    BigNumber operator*=(const BigNumber &other);

    BigNumber operator/=(const BigNumber &other);

    BigNumber operator+=(const long long &other);

    BigNumber operator-=(const long long &other);

    BigNumber operator*=(const long long &other);

    BigNumber operator/=(const long long &other);

    // Перегрузка операторов сравнения
    bool operator==(const BigNumber &other) const;

    bool operator!=(const BigNumber &other) const;

    bool operator<(const BigNumber &other) const;

    bool operator>(const BigNumber &other) const;

    bool operator<=(const BigNumber &other) const;

    bool operator>=(const BigNumber &other) const;

    // Вычисление степени
    BigNumber power(int n) const;

    // Взятие квадратного корня

    BigNumber sqrt() const;

    BigNumber arctan() const;

    BigNumber abs() const;

    static BigNumber calculatePiViaArctangents(int precision);

    void change_precision(int precision);
};

BigNumber operator""_m(const char* number);
