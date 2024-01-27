#include <iostream>
#include <string>

using namespace std;

class BigNumber {
private:
    string integerPart;  // Целая часть числа
    string decimalPart;  // Десятичная часть числа (до заданной точности)
    bool negative;       // Флаг отрицательности числа
    size_t precision;    // Точность после запятой

    void normalize() {
        // Удаляем лидирующие нули из целой части, кроме случая когда число равно 0
        while (integerPart.length() > 1 && integerPart.front() == '0') {
            integerPart.erase(integerPart.begin());
        }

        // Обрезаем или добавляем нули в дробную часть для достижения необходимой точности
        if (decimalPart.length() > precision) {
            decimalPart.erase(decimalPart.begin() + precision, decimalPart.end());
        } else {
            while (decimalPart.length() < precision) {
                decimalPart.push_back('0');
            }
        }
    }

public:
    // Конструктор из строки
    BigNumber(const string& number, size_t precision) : negative(false), precision(precision) {
        string::const_iterator it = number.begin();

        if (it != number.end() && (*it == '-' || *it == '+')) {
            negative = (*it == '-');
            ++it;
        }

        // Цикл до десятичной точки
        while (it != number.end() && *it != '.') {
            if (isdigit(*it)) {
                integerPart.push_back(*it);
            }
            ++it;
        }

        // Если целая часть пустая, значит начало числа это 0
        if (integerPart.empty()) {
            integerPart = "0";
        }

        // Пропускаем десятичную точку
        if (it != number.end() && *it == '.') {
            ++it;
        }

        // Цикл после десятичной точки
        while (it != number.end()) {
            if (isdigit(*it)) {
                decimalPart.push_back(*it);
            }
            ++it;
        }

        // Нормализация числа
        normalize();
    }

    // Конструктор из float
    BigNumber(float number, size_t precision);

    // Конструктор из double
    BigNumber(double number, size_t precision);

    // Метод для получения строкового представления числа
    string ToString() const {
        string numberString;

        if (negative && (integerPart != "0" || decimalPart != string(precision, '0'))) {
            numberString += '-';
        }

        numberString += integerPart;

        if (precision > 0) {
            numberString += '.';
            numberString += decimalPart;
        }

        return numberString;
    };

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

    // Дополнительные методы могут быть добавлены здесь, например:
    // - методы для внутренней нормализации числа
    // - операторы +=, -=, *=, /=
    // - операторы сравнения <=, >=
};

int main() {
    BigNumber n1("12.32", 5);

    cout << n1.ToString() << endl;
    return 0;
}