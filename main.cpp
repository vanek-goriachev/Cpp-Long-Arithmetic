#include <iostream>
#include <string>
#include <cmath>

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
    BigNumber(float number, size_t prec) : precision(prec), negative(number < 0) {
        // Используем тернарный оператор, чтобы установить значение флага отрицательности
        if (number < 0) {
            number = -number; // Работаем с числом как с положительным
        }

        // Вычисляем множитель для заданной точности
        float multiplier = pow(10.0f, precision);

        // Округляем число до заданной точности
        number = round(number * multiplier) / multiplier;

        // Получаем целую часть числа
        auto integerPartNumber = static_cast<long long>(number);
        integerPart = to_string(integerPartNumber);

        // Получаем дробную часть числа
        float decimalPartNumber = number - static_cast<float>(integerPartNumber);
        auto decimalPartAsInt = static_cast<long long>(round(decimalPartNumber * multiplier));

        decimalPart = to_string(decimalPartAsInt);

        // Дополняем дробную часть нулями, если она короче нужной точности
        while (decimalPart.length() < precision) {
            decimalPart = "0" + decimalPart;
        }

        // Если округление дало нам "1000" в decimalPart при precision 3, необходимо перенести '1' в integerPart
        if (decimalPart.length() > precision) {
            // Добавляем переносимый '1' к целой части
            integerPart = to_string(integerPartNumber + 1);

            // Обрезаем "1000" до "000" в decimalPart
            decimalPart = decimalPart.substr(1);
        }
    }

    // Конструктор из double
    BigNumber(double number, size_t prec) : precision(prec), negative(number < 0) {
        // Используем тернарный оператор, чтобы установить значение флага отрицательности
        if (number < 0) {
            number = -number; // Работаем с числом как с положительным
        }

        // Вычисляем множитель для заданной точности
        float multiplier = pow(10.0f, precision);

        // Округляем число до заданной точности
        number = round(number * multiplier) / multiplier;

        // Получаем целую часть числа
        auto integerPartNumber = static_cast<long long>(number);
        integerPart = to_string(integerPartNumber);

        // Получаем дробную часть числа
        float decimalPartNumber = number - static_cast<float>(integerPartNumber);
        auto decimalPartAsInt = static_cast<long long>(round(decimalPartNumber * multiplier));

        decimalPart = to_string(decimalPartAsInt);

        // Дополняем дробную часть нулями, если она короче нужной точности
        while (decimalPart.length() < precision) {
            decimalPart = "0" + decimalPart;
        }

        // Если округление дало нам "1000" в decimalPart при precision 3, необходимо перенести '1' в integerPart
        if (decimalPart.length() > precision) {
            // Добавляем переносимый '1' к целой части
            integerPart = to_string(integerPartNumber + 1);

            // Обрезаем "1000" до "000" в decimalPart
            decimalPart = decimalPart.substr(1);
        }
    }

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
    BigNumber n1("-12.01234567890123456789", 10);
    cout << n1.ToString() << endl;

    BigNumber n2(float(-12.0123456789), 5);
    cout << n2.ToString() << endl;

    BigNumber n3(-12.01234567890123456789, 12);
    cout << n3.ToString() << endl; // из численного значения перевод работает не слишком хорошо
    cout << -12.01234567890123456789 << endl;
    return 0;
}