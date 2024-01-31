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
            } else
            {
                throw invalid_argument("Initial string for BigNumber should satisfy pattern [+-]{0-9}.{0-9}");
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
            } else
            {
                throw invalid_argument("Initial string for BigNumber should satisfy pattern [+-]{0-9}.{0-9}");
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

    // Конструктор из long long
    BigNumber(long long number, size_t prec) : precision(prec)
    {
        // Проверка на отрицательное значение и установка флага
        if (number < 0)
        {
            negative = true;
            number = -number; // Работаем с числом как с положительным
        } else
        {
            negative = false;
        }

        // Преобразование числа в строку для целой части
        integerPart = to_string(number);

        // Десятичная часть будет состоять из нулей, так как исходное число целое
        decimalPart = string(precision, '0');
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
        size_t thisIntegerPartLength = this->integerPart.length();
        size_t otherIntegerPartLength = other.integerPart.length();

        size_t maxSize = max(thisIntegerPartLength, otherIntegerPartLength);
        string resultIntegerPart(maxSize, '0'); // Временно хранение целой части результата

        for (int i = 0; i < maxSize; i += 1)
        {
            int digit1 =
                    i < thisIntegerPartLength ? this->integerPart[thisIntegerPartLength - i - 1] - '0' : 0;
            int digit2 =
                    i < otherIntegerPartLength ? other.integerPart[otherIntegerPartLength - i - 1] - '0' : 0;
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
            throw invalid_argument("Precision mismatch between BigNumber operands.");
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
        if (*this < other ^ this->negative)
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
            int digit2 = i < this->precision ? smallerDecPart[i] - '0' : 0;
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
        int productNumberLength = integerPart.length() + other.integerPart.length() +
                                  precision + other.precision;
        string product(productNumberLength, '0');

        string thisNumber = this->integerPart + this->decimalPart;
        string otherNumber = other.integerPart + other.decimalPart;

        int thisNumberLength = thisNumber.length(),
                otherNumberLength = otherNumber.length();

        // Умножение без учета десятичной точки (как если бы числа были целыми)
        for (int i = thisNumberLength - 1; i >= 0; --i)
        {
            for (int j = otherNumberLength - 1; j >= 0; --j)
            {
                int productIndex = (thisNumberLength - 1 - i) + (otherNumberLength - 1 - j);
                int digitProduct = (thisNumber[i] - '0') * (otherNumber[j] - '0') +
                                   (product[productNumberLength - 1 - productIndex] - '0');

                product[productNumberLength - 1 - productIndex] = (digitProduct % 10) + '0';
                int carry = digitProduct / 10;
                int k = productIndex + 1;

                // Обрабатываем перенос на следующие позиции
                while (carry > 0)
                {
                    digitProduct = (product[productNumberLength - 1 - k] - '0') + carry;
                    product[productNumberLength - 1 - k] = (digitProduct % 10) + '0';
                    carry = digitProduct / 10;
                    ++k;
                }
            }
        }

        // Разделение на целую и дробную часть
        if (result.precision != 0)
        {
            if (productNumberLength > result.precision)
            {
                result.decimalPart = product.substr(productNumberLength - result.precision);
                result.integerPart = product.substr(0, productNumberLength - result.precision);
            } else
            {
                result.decimalPart = string(result.precision - productNumberLength, '0') + product;
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

    BigNumber operator/(const BigNumber &other) const
    {
        // Проверка деления на ноль
        if (other.integerPart == "0" && other.decimalPart == string(other.precision, '0'))
        {
            throw invalid_argument("Division by zero is not allowed.");
        }

        // Если точность выше, чем необходимо, временно увеличим её для проведения точного деления
        size_t bufferSize = this->precision; // Если в результате получается периодическая дробь, то буфер должен быть больше длины периода
        size_t tempPrecision = this->precision + bufferSize; // Например, добавляем 5 знаков для буфера
        string thisNumber = this->integerPart + this->decimalPart + string(bufferSize, '0');
        string otherNumber = other.integerPart + other.decimalPart;

        string quotient = "0";
        string remainder = "0";

        int thisNumberLength = thisNumber.length(), thisNumberIntegerLength = this->integerPart.length();

        // Алгоритм деления в столбик
        for (size_t i = 0; i < thisNumberLength; ++i)
        {
            // "Опускаем" следующую цифру
            remainder += thisNumber[i];

            // Если цифру, которую опустили, была из дробной части
            // Но также нам нужно снести столько цифр, сколько находится в дробной части второго числа
            if (i == thisNumberIntegerLength + other.precision)
            {
                quotient += ".";
            }

            // Избавляемся от лидирующих нулей в остатке
            size_t startPos = remainder.find_first_not_of('0');
            if (startPos != string::npos)
            {
                remainder = remainder.substr(startPos);
            } else
            {
                remainder = "0";
            }

            // Находим максимальное число, при умножении на которое otherNumber не превысит remainder
            int count = 0;
            BigNumber tempRemainder(remainder, tempPrecision);
            BigNumber tempOtherNumber(otherNumber, tempPrecision);
            while (tempRemainder >= tempOtherNumber)
            {
                tempRemainder = tempRemainder - tempOtherNumber;
                remainder = tempRemainder.integerPart;
                ++count;
            }

            // Добавляем найденную цифру к частному
            quotient += to_string(count);
        }

        BigNumber result1(quotient, this->precision);
        result1.negative = this->negative != other.negative; // Определение знака результата

        return result1;
    }

    // Перегрузка оператора унарный минус
    BigNumber operator-() const
    {
        BigNumber result(*this);
        result.negative = !result.negative;
        return result;
    };

    BigNumber operator+(const long long &other)
    {
        return *this + BigNumber(other, this->precision);
    };

    BigNumber operator-(const long long &other)
    {
        return *this - BigNumber(other, this->precision);
    };

    BigNumber operator*(const long long &other)
    {
        return *this * BigNumber(other, this->precision);
    };

    BigNumber operator/(const long long &other)
    {
        return *this / BigNumber(other, this->precision);
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

    BigNumber operator+=(const BigNumber &other)
    {
        *this = *this + other;
        return *this;
    };

    BigNumber operator-=(const BigNumber &other)
    {
        *this = *this - other;
        return *this;
    };

    BigNumber operator*=(const BigNumber &other)
    {
        *this = *this * other;
        return *this;
    };

    BigNumber operator/=(const BigNumber &other)
    {
        *this = *this / other;
        return *this;
    };

    BigNumber operator+=(const long long &other)
    {
        *this = *this + BigNumber(other, this->precision);
        return *this;
    };

    BigNumber operator-=(const long long &other)
    {
        *this = *this - BigNumber(other, this->precision);
        return *this;
    };

    BigNumber operator*=(const long long &other)
    {
        *this = *this * BigNumber(other, this->precision);
        return *this;
    };

    BigNumber operator/=(const long long &other)
    {
        *this = *this / BigNumber(other, this->precision);
        return *this;
    };

    // Перегрузка операторов сравнения
    bool operator==(const BigNumber &other) const
    {
        if (this->precision != other.precision)
        {
            throw invalid_argument("Precision mismatch between BigNumber operands.");
        }

        // Проверяем целые части чисел на равенство
        string thisInt = this->integerPart;
        string otherInt = other.integerPart;

        // Убираем ведущие нули для сравнения
        thisInt.erase(0, min(thisInt.find_first_not_of('0'), thisInt.size() - 1));
        otherInt.erase(0, min(otherInt.find_first_not_of('0'), otherInt.size() - 1));

        if (thisInt != otherInt) return false;

        // Дополняем десятичные части нулями справа до равной длины
        string thisDec = this->decimalPart;
        string otherDec = other.decimalPart;

        int thisDecimalLength = thisDec.length();
        int otherDecimalLength = otherDec.length();

        if (thisDecimalLength < otherDecimalLength)
        {
            thisDec.append(otherDecimalLength - thisDecimalLength, '0');
        } else if (otherDecimalLength < thisDecimalLength)
        {
            otherDec.append(thisDecimalLength - otherDecimalLength, '0');
        }

        // Сравниваем десятичные части
        if (thisDec != otherDec) return false;

        // Если оба числа равны нулю
        if (thisInt == "0" && thisDec == string(this->precision, '0')) return true;

        // Проверяем знаки чисел
        return this->negative == other.negative;
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
            if (this->integerPart.length() == other.integerPart.length())
            {
                return this->integerPart < other.integerPart ^ this->negative;
            }
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

    // Вычисление степени
    BigNumber power(int n) const
    {
        // Обработка отрицательных и нулевых показателей степени
        if (n < 0)
        {
            throw invalid_argument("BigNumber::power - negative exponents are not supported.");
        } else if (n == 0)
        {
            return BigNumber("1", this->precision); // Любое число в степени 0 равно 1
        }

        BigNumber result = *this; // Начинаем с текущего числа для n = 1
        result.precision = this->precision * 5;
        result.normalize();

        BigNumber newThis = *this; // Начинаем с текущего числа для n = 1
        newThis.precision = this->precision * 5;
        newThis.normalize();

        for (int i = 1; i < n; ++i)
        {
            result *= newThis; // Повторное умножение для вычисления степени
        }

        result.precision = this->precision;
        result.normalize();

        return result;
    }

    // Взятие квадратного корня

    BigNumber sqrt() const
    {
        // Проверка на отрицательное число
        if (this->negative)
        {
            throw invalid_argument("Cannot take the square root of a negative number.");
        }

        // Проверка, является ли число нулем
        if (this->integerPart == "0" && this->decimalPart == string(this->precision, '0'))
        {
            return BigNumber("0", this->precision);
        }
        if (this->integerPart == "1" && this->decimalPart == string(this->precision, '0'))
        {
            return BigNumber("1", this->precision);
        }

        // Начальное приближение – половина числа
        BigNumber guess(*this), zero("0", precision), two("2", precision);
        guess.decimalPart = string(precision, '0');
        guess = guess / two;

        // Уточнение предположения с помощью метода Ньютона до достижения необходимой точности
        BigNumber lastGuess("0", this->precision);

        do
        {
            lastGuess = guess; // Сохраняем последнее предположение
            guess = guess - (guess * guess - *this) / (two * guess);
        } while (guess != lastGuess);

        return guess;
    }

    BigNumber arctan() const
    {
        if (*this > BigNumber("1", precision) || *this < BigNumber("-1", precision))
        {
            throw std::invalid_argument("The arctan function is only implemented for |x| <= 1.");
        }

        BigNumber term = *this; // x^1 / 1
        BigNumber arctanValue = term; // Начинаем с первого члена ряда

        BigNumber xSquared = *this * *this; // x^2, будет использоваться для вычисления каждого нового члена
        BigNumber divisor("1", precision); // Делитель для n

        for (size_t n = 1;; n += 2)
        {
            // Вычисляем следующий член, используя предыдущий
            term *= -xSquared;
            divisor += BigNumber("2", precision); // Увеличиваем делитель на 2 для каждого нового члена ряда

            BigNumber nextTerm = term / divisor;

            // Если следующий член ряда достаточно мал, останавливаем вычисления
            if (nextTerm.ToString() == BigNumber("0", precision).ToString())
            {
                break;
            }

            // Добавляем следующий член к значению арктангенса
            arctanValue += nextTerm;
        }

        return arctanValue;
    }

    BigNumber abs() const
    {
        BigNumber result(*this);
        result.negative = false;
        return result;
    }

    static BigNumber calculatePiViaArctangents(int precision)
    {
        // https://www.youtube.com/watch?v=yxZcFt0yZfg <--- this one helped
        // https://youtu.be/6A75VBWXp2Y?si=CWKrnqiiXvqS6Fb0&t=1076
        // https://youtu.be/A3PL61fHzjs?si=Ylpw3Jh93Tl31pDs&t=958
        precision += 10;
        BigNumber one("1", precision), two("2", precision),
                three("3", precision), four("4", precision);

        BigNumber Pi1 = four * ((one / two).arctan() + (one / three).arctan());
        Pi1.precision -= 10;
        Pi1.normalize();

        return Pi1;
    }
};

BigNumber operator"" _m(long double meters)
{
    return BigNumber(static_cast<double>(meters), 20);
}

int main()
{
//    // Проверка конструктора из строкового значения
//    BigNumber n1("-123.11234", 5);
//    cout << "n1 = " << n1.ToString() << endl;
//
//    // Проверка конструктора из float значения
//    BigNumber n2(float(-2.0123456789), 5);
//    cout << "n2 = " << n2.ToString() << endl;
//
//    // Проверка конструктора из double значения
//    BigNumber n3(0990912.01235, 5);
//    cout << "n3 = " << n3.ToString() << endl;
//    cout << endl;
//
//    // Проверка унарного минуса
//    cout << "n1 * (-1): " << n1.ToString() << " * (-1) = " << (-n1).ToString() << endl;
//    cout << "n3 * (-1): " << n3.ToString() << " * (-1) = " << (-n3).ToString() << endl;
//    cout << endl;
//
//    // Проверка сложения
//    cout << "n1 + n2: " << (n1 + n2).ToString() << endl;
//    cout << "n3 + n3: " << (n3 + n3).ToString() << endl;
//    // Тут по сути вычитание
//    cout << "n3 + n1: " << (n3 + n1).ToString() << endl;
//    cout << endl;
//
//    // Проверка вычитания
//    cout << "n1 - n2: " << (n1 - n2).ToString() << endl;
//    cout << "n3 - n3: " << (n3 - n3).ToString() << endl;
//    // Тут по сути сложение
//    cout << "n3 - n2: " << (n3 - n2).ToString() << endl;
//    cout << endl;
//
//    // Проверка умножения
//    BigNumber n4("-123.234", 5);
//    BigNumber n5(float(2.0962), 5);
//    cout << "n4 = " << n4.ToString() << endl;
//    cout << "n5 = " << n5.ToString() << endl;
//
//    cout << "n4 * n4: " << (n4 * n4).ToString() << endl;
//    cout << "n5 * n5: " << (n5 * n5).ToString() << endl;
//    cout << "n4 * n5: " << (n4 * n5).ToString() << endl;
//    cout << endl;
//
    // Проверка деления
    BigNumber nd11 = 12465423._m,  nd12 = 834812._m;
    BigNumber nd21("19513", 15),  nd22("83481", 15);
    BigNumber nd31("226", 15),  nd32("15", 15);
    BigNumber nd41("8419.34", 15),  nd42("193.6", 15);
    BigNumber nd51("12465.423", 15),  nd52("83.4812", 15);

    cout << nd11.ToString() << " / " << nd12.ToString() << " = " << (nd11 / nd12).ToString() << endl;
    cout << nd21.ToString() << " / " << nd22.ToString() << " = " << (nd21 / nd22).ToString() << endl;
    cout << nd31.ToString() << " / " << nd32.ToString() << " = " << (nd31 / nd32).ToString() << endl;
    cout << nd41.ToString() << " / " << nd42.ToString() << " = " << (nd41 / nd42).ToString() << endl;
    cout << nd51.ToString() << " / " << nd52.ToString() << " = " << (nd51 / nd52).ToString() << endl;
    cout << endl;
//
//    // Проверка валидации при создании
//    BigNumber n9("+123.12", 5);
//    string args[] = {"123.12",
//                     "+123.12",
//                     "-123.12",
//                     ".12",
//                     "+.12",
//                     "-.12",
//                     "12.",
//                     "+12.",
//                     "-12.",
//                     "12",
//                     "+12",
//                     "-12",
//                     "0.0",
//                     "."};
//    for (const auto &item: args)
//    {
//        n9 = BigNumber(item, 5);
//        cout << item << " -> " << n9.ToString() << endl;
//    }
//    cout << endl;
//
//
//    // Проверка взятия корня
//    BigNumber n10("514", 10);
//    BigNumber n11("7", 10);
//    BigNumber n12("1", 10);
//    cout << "n10 = " << n10.ToString() << endl;
//    cout << "n11 = " << n11.ToString() << endl;
//    cout << "n12 = " << n12.ToString() << endl;
//
//    cout << "sqrt(n10) = " << n10.sqrt().ToString() << endl;
//    cout << "sqrt(n11) = " << n11.sqrt().ToString() << endl;
//    cout << "sqrt(n12) = " << n12.sqrt().ToString() << endl;
//    cout << endl;
//
//
//    // Проверка возведения в степень
//    BigNumber n13("2", 10);
//    BigNumber n14("1.01", 10);
//    cout << "n13 = " << n13.ToString() << endl;
//    cout << "n14 = " << n14.ToString() << endl;
//
//    cout << "n13 ** 8 = " << n13.power(8).ToString() << endl;
//    cout << "n14 ** 365 = " << n14.power(365).ToString() << endl;
//    cout << endl;
//
//
//    // Проверка арктангенса
//    BigNumber n15("0.5", 10);
//    cout << n15.arctan().ToString() << endl;
//    cout << endl;
    clock_t start = clock();


    BigNumber magicNumber = BigNumber::calculatePiViaArctangents(100);
    cout << magicNumber.ToString() << endl;


    clock_t end = clock();
    double seconds = (double) (end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);

    return 0;
}