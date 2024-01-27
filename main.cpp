#include <iostream>
#include <string>

using namespace std;

class BigNumber {
private:
    string integerPart;  // Целая часть числа
    string decimalPart;  // Десятичная часть числа (до заданной точности)
    bool negative;       // Флаг отрицательности числа
    size_t precision;    // Точность после запятой

public:
    // Конструктор из строки
    BigNumber(const string& number, size_t precision);

    // Конструктор из float
    BigNumber(float number, size_t precision);

    // Конструктор из double
    BigNumber(double number, size_t precision);

    // Метод для получения строкового представления числа
    string ToString() const;

    // Перегрузка арифметических операторов
    BigNumber operator+(const BigNumber& other) const;
    BigNumber operator-(const BigNumber& other) const;
    BigNumber operator*(const BigNumber& other) const;
    BigNumber operator/(const BigNumber& other) const;

    // Перегрузка оператора присваивания
    BigNumber& operator=(const BigNumber& other);

    // Перегрузка операторов сравнения
    bool operator==(const BigNumber& other) const;
    bool operator!=(const BigNumber& other) const;
    bool operator<(const BigNumber& other) const;
    bool operator>(const BigNumber& other) const;

    // Деструктор
    ~BigNumber();

    // Дополнительные методы могут быть добавлены здесь, например:
    // - методы для внутренней нормализации числа
    // - операторы +=, -=, *=, /=
    // - операторы сравнения <=, >=
};

int main() {
    cout << "Hello world" << endl;
    return 0;
}