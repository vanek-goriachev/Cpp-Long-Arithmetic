#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class BigNumber
{
private:
    string integerPart;  // Целая часть числа
    string decimalPart;  // Десятичная часть числа (до заданной точности)
    bool negative;       // Флаг отрицательности числа
    size_t precision;    // Точность после запятой

    void normalize()
    {
        // Удаляем лидирующие нули из целой части, кроме случая когда число равно 0
        while (integerPart.length() > 1 && integerPart.front() == '0')
        {
            integerPart.erase(integerPart.begin());
        }

        // Обрезаем или добавляем нули в дробную часть для достижения необходимой точности
        if (decimalPart.length() > precision)
        {
            decimalPart.erase(decimalPart.begin() + precision, decimalPart.end());
        } else
        {
            while (decimalPart.length() < precision)
            {
                decimalPart.push_back('0');
            }
        }
    }

public:
    // Конструктор из BigNumber
    BigNumber(const BigNumber &other) : negative(other.negative), precision(other.precision),
                                        integerPart(other.integerPart), decimalPart(other.decimalPart)
    {
        // Нормализация числа
        normalize();
    }

    // Конструктор из строки
    BigNumber(const string &number, size_t precision) : negative(false), precision(precision)
    {
        string::const_iterator it = number.begin();

        if (it != number.end() && (*it == '-' || *it == '+'))
        {
            negative = (*it == '-');
            ++it;
        }

        // Цикл до десятичной точки
        while (it != number.end() && *it != '.')
        {
            if (isdigit(*it))
            {
                integerPart.push_back(*it);
            }
            ++it;
        }

        // Если целая часть пустая, значит начало числа это 0
        if (integerPart.empty())
        {
            integerPart = "0";
        }

        // Пропускаем десятичную точку
        if (it != number.end() && *it == '.')
        {
            ++it;
        }

        // Цикл после десятичной точки
        while (it != number.end())
        {
            if (isdigit(*it))
            {
                decimalPart.push_back(*it);
            }
            ++it;
        }

        // Нормализация числа
        normalize();
    }

    // Конструктор из float
    BigNumber(float number, size_t prec) : precision(prec), negative(number < 0)
    {
        // Используем тернарный оператор, чтобы установить значение флага отрицательности
        if (number < 0)
        {
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
        while (decimalPart.length() < precision)
        {
            decimalPart = "0" + decimalPart;
        }

        // Если округление дало нам "1000" в decimalPart при precision 3, необходимо перенести '1' в integerPart
        if (decimalPart.length() > precision)
        {
            // Добавляем переносимый '1' к целой части
            integerPart = to_string(integerPartNumber + 1);

            // Обрезаем "1000" до "000" в decimalPart
            decimalPart = decimalPart.substr(1);
        }
    }

    // Конструктор из double
    BigNumber(double number, size_t prec) : precision(prec), negative(number < 0)
    {
        // Используем тернарный оператор, чтобы установить значение флага отрицательности
        if (number < 0)
        {
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
        while (decimalPart.length() < precision)
        {
            decimalPart = "0" + decimalPart;
        }

        // Если округление дало нам "1000" в decimalPart при precision 3, необходимо перенести '1' в integerPart
        if (decimalPart.length() > precision)
        {
            // Добавляем переносимый '1' к целой части
            integerPart = to_string(integerPartNumber + 1);

            // Обрезаем "1000" до "000" в decimalPart
            decimalPart = decimalPart.substr(1);
        }
    }

    // Метод для получения строкового представления числа
    string ToString() const
    {
        string numberString;

        if (negative && (integerPart != "0" || decimalPart != string(precision, '0')))
        {
            numberString += '-';
        }

        numberString += integerPart;

        if (precision > 0)
        {
            numberString += '.';
            numberString += decimalPart;
        }

        return numberString;
    };

    // Перегрузка арифметических операторов
    BigNumber operator+(const BigNumber &other) const
    {
        // Проверяем, что точность обоих операндов одинакова
        if (this->precision != other.precision)
        {
            throw invalid_argument("Precision mismatch between BigNumber operands.");
        }

        BigNumber result("0", this->precision); // Инициализируем результирующее число

        // Если числа имеют разные знаки, используем вычитание
        if (this->negative != other.negative)
        {
            result = other - (-*this);
            return result;
        }

        // Далее можно быть уверенными, что при сложении операндов с одним знаком он сохранится
        result.negative = this->negative;

        // Сложение дробной части
        int carry = 0; // Перенос из предыдущего разряда
        for (int i = precision - 1; i >= 0; --i)
        {
            int sum = (this->decimalPart[i] - '0') + (other.decimalPart[i] - '0') + carry;
            result.decimalPart[i] = (sum % 10) + '0';
            carry = sum / 10; // Сохраняем перенос для следующего шага
        }

        // Сложение целой части
        size_t maxSize = max(this->integerPart.length(), other.integerPart.length());
        string resultIntegerPart(maxSize, '0'); // Временно хранение целой части результата

        for (int i = 0; i < maxSize; i += 1)
        {
            int digit1 =
                    i < this->integerPart.length() ? this->integerPart[this->integerPart.length() - i - 1] - '0' : 0;
            int digit2 =
                    i < other.integerPart.length() ? other.integerPart[other.integerPart.length() - i - 1] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            resultIntegerPart[maxSize - i - 1] = (sum % 10) + '0';
            carry = sum / 10;
        }

        // Если в конце остался перенос, добавляем его к результату
        if (carry > 0)
        {
            resultIntegerPart = static_cast<char>(carry + '0') + resultIntegerPart;
        }

        result.integerPart = resultIntegerPart;

        return result;
    }

    BigNumber operator-(const BigNumber &other) const
    {
        // Проверяем, что точность обоих операндов одинакова
        if (this->precision != other.precision)
        {
            throw std::invalid_argument("Precision mismatch between BigNumber operands.");
        }

        BigNumber result("0", this->precision); // Инициализируем результирующее число
        bool resultIsNegative = false; // Используется для хранения знака результата

        // Если числа имеют разные знаки, используем сложение
        if (this->negative != other.negative)
        {
            result = *this + (-other);
            return result;
        }

        // Определение, какое число больше по абсолютной величине для корректного вычитания
        bool swapOperands = false;
        if (this->integerPart.length() < other.integerPart.length() ||
            (this->integerPart.length() == other.integerPart.length() &&
             this->integerPart.compare(other.integerPart) < 0))
        {
            swapOperands = true;
        }

        const string &largerIntPart = swapOperands ? other.integerPart : this->integerPart;
        const string &smallerIntPart = swapOperands ? this->integerPart : other.integerPart;
        const string &largerDecPart = swapOperands ? other.decimalPart : this->decimalPart;
        const string &smallerDecPart = swapOperands ? this->decimalPart : other.decimalPart;

        resultIsNegative = swapOperands ? !other.negative : this->negative;

        string resultIntegerPart = string(max(largerIntPart.size(), smallerIntPart.size()), '0');
        string resultDecimalPart = string(this->precision, '0');

        // Вычитание дробной части
        int carry = 0;
        for (int i = precision - 1; i >= 0; --i)
        {
            int digit1 = largerDecPart[i] - '0';
            int digit2 = i < smallerDecPart.length() ? smallerDecPart[i] - '0' : 0;
            int diff = digit1 - digit2 - carry;
            if (diff < 0)
            {
                diff += 10;
                carry = 1;
            } else
            {
                carry = 0;
            }
            resultDecimalPart[i] = diff + '0';
        }

        // Вычитание целой части
        for (int i = resultIntegerPart.length() - 1, j = smallerIntPart.length() - 1; i >= 0; --i, --j)
        {
            int digit1 = largerIntPart[i] - '0';
            int digit2 = j >= 0 ? smallerIntPart[j] - '0' : 0;
            int diff = digit1 - digit2 - carry;
            if (diff < 0)
            {
                diff += 10;
                carry = 1;
            } else
            {
                carry = 0;
            }
            resultIntegerPart[i] = diff + '0';
        }

        // Обрезаем лидирующие нули в целой части
        auto nonZeroPos = resultIntegerPart.find_first_not_of('0');
        if (nonZeroPos == string::npos)
        {
            nonZeroPos = resultIntegerPart.size() - 1;
        }
        resultIntegerPart = resultIntegerPart.substr(nonZeroPos);

        result.integerPart = resultIntegerPart;
        result.decimalPart = resultDecimalPart;
        result.negative = resultIsNegative;

        return result;
    }

    BigNumber operator*(const BigNumber &other) const
    {
        // Проверяем, что точность обоих операндов одинакова (в данном случае это не обязательно, но пусть будет)
        if (this->precision != other.precision)
        {
            throw invalid_argument("Precision mismatch between BigNumber operands.");
        }

        // Инициализация результата умножения с верной точностью
        BigNumber result("0", this->precision + other.precision);

        // После умножения результат может иметь максимум такое количество цифр
        string product(integerPart.length() + other.integerPart.length() +
                       decimalPart.length() + other.decimalPart.length(), '0');

        string thisNumber = this->integerPart + this->decimalPart;
        string otherNumber = other.integerPart + other.decimalPart;

        // Умножение без учета десятичной точки (как если бы числа были целыми)
        for (int i = thisNumber.length() - 1; i >= 0; --i)
        {
            for (int j = otherNumber.length() - 1; j >= 0; --j)
            {
                int productIndex = (thisNumber.length() - 1 - i) + (otherNumber.length() - 1 - j);
                int digitProduct = (thisNumber[i] - '0') * (otherNumber[j] - '0') +
                                   (product[product.length() - 1 - productIndex] - '0');

                product[product.length() - 1 - productIndex] = (digitProduct % 10) + '0';
                int carry = digitProduct / 10;
                int k = productIndex + 1;

                // Обрабатываем перенос на следующие позиции
                while (carry > 0)
                {
                    digitProduct = (product[product.length() - 1 - k] - '0') + carry;
                    product[product.length() - 1 - k] = (digitProduct % 10) + '0';
                    carry = digitProduct / 10;
                    ++k;
                }
            }
        }

        // Разделение на целую и дробную часть
        if (result.precision != 0)
        {
            if (product.length() > result.precision)
            {
                result.decimalPart = product.substr(product.length() - result.precision);
                result.integerPart = product.substr(0, product.length() - result.precision);
            } else
            {
                result.decimalPart = string(result.precision - product.length(), '0') + product;
                result.integerPart = "0";
            }
        } else
        {
            result.integerPart = product;
        }

        // Установка знака результата
        result.negative = this->negative != other.negative;

        // Установка точности результата - такая же, как у операндов
        result.precision = this->precision;

        result.normalize();

        return result;
    }


    BigNumber operator/(const BigNumber &other) const;

    // Перегрузка оператора унарный минус
    BigNumber operator-() const
    {
        BigNumber result(*this);
        result.negative = !result.negative;
        return result;
    };

    // Перегрузка оператора присваивания
    BigNumber &operator=(const BigNumber &other)
    {
        if (this != &other)
        { // Проверка на самоприсваивание
            integerPart = other.integerPart;
            decimalPart = other.decimalPart;
            negative = other.negative;
            precision = other.precision;
        }
        return *this; // Возврат ссылки на текущий объект
    }

    // Перегрузка операторов сравнения
    bool operator==(const BigNumber &other) const
    {
        return this->negative == other.negative &&
               this->integerPart == other.integerPart &&
               this->decimalPart == other.decimalPart;
    }

    bool operator!=(const BigNumber &other) const
    {
        return !(*this == other);
    }

    bool operator<(const BigNumber &other) const
    {
        if (this->negative != other.negative)
        {
            return this->negative; // Если одно число отрицательное, а другое положительное
        }
        if (this->integerPart != other.integerPart)
        {
            // Числа с более длинной целой частью больше
            return this->integerPart.length() < other.integerPart.length() ^
                   this->negative; // Если числа отрицательные, меньшее число будет иметь большую целую часть
        }
        // Если целые части равны, сравниваем десятичные части
        return this->decimalPart < other.decimalPart ^ this->negative;
    }

    bool operator>(const BigNumber &other) const
    {
        return other < *this;
    }

    bool operator<=(const BigNumber &other) const
    {
        return !(*this > other);
    }

    bool operator>=(const BigNumber &other) const
    {
        return !(*this < other);
    }
};

int main()
{
    // Проверка конструктора из строкового значения
    BigNumber n1("-123.11234", 5);
    cout << "n1 = " << n1.ToString() << endl;

    // Проверка конструктора из float значения
    BigNumber n2(float(-2.0123456789), 5);
    cout << "n2 = " << n2.ToString() << endl;

    // Проверка конструктора из double значения
    BigNumber n3(0990912.01235, 5);
    cout << "n3 = " << n3.ToString() << endl;
    cout << endl;

    // Проверка унарного минуса
    cout << "n1 * (-1): " << n1.ToString() << " * (-1) = " << (-n1).ToString() << endl;
    cout << "n3 * (-1): " << n3.ToString() << " * (-1) = " << (-n3).ToString() << endl;
    cout << endl;

    // Проверка сложения
    cout << "n1 + n2: " << (n1 + n2).ToString() << endl;
    cout << "n3 + n3: " << (n3 + n3).ToString() << endl;
    // Тут по сути вычитание
    cout << "n3 + n1: " << (n3 + n1).ToString() << endl;
    cout << endl;

    // Проверка вычитания
    cout << "n1 - n2: " << (n1 - n2).ToString() << endl;
    cout << "n3 - n3: " << (n3 - n3).ToString() << endl;
    // Тут по сути сложение
    cout << "n3 - n2: " << (n3 - n2).ToString() << endl;
    cout << endl;

    // Проверка умножения
    BigNumber n4("-123.234", 5);
    BigNumber n5(float(2.0962), 5);
    cout << "n4 = " << n4.ToString() << endl;
    cout << "n5 = " << n5.ToString() << endl;

    cout << "n4 * n4: " << (n4 * n4).ToString() << endl;
    cout << "n5 * n5: " << (n5 * n5).ToString() << endl;
    cout << "n4 * n5: " << (n4 * n5).ToString() << endl;
    cout << endl;
    return 0;
}