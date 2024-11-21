#include <iostream>
#include <cmath>
#include <locale>
#include <limits>

void f1(double, double);

int main()
{
    std::locale::global(std::locale("Russian_Russia.1251"));
    std::cout.imbue(std::locale());

    double a, b, t2;

    std::cout << "Введите a, b: ";
    std::cin >> a >> b;

    if ((a == 0) || (b == 0))  f1(a, b);

    if (a * b > 0.5)
    {
        t2 = std::exp(-((std::fabs(a) + std::fabs(b)) / 2)) * (1 / std::tan(a));
        std::cout << "\n Результат 1: t2=" << t2 << "\n";
    }

    if (0.4 < a * b && a * b <= 0.5)
    {
        t2 = std::fabs(a + std::pow(b, 2)) * (1 / std::tan(b));
        std::cout << "\n Результат 2: t2=" << t2 << "\n";
    }

    std::cin.get(); // Pause the program
    return 0;
}

void f1(double a, double b)
{
    std::cout << "\n Нет решения для a=" << a << ", b=" << b << "\n";

    std::cout << "\n Введите a, b: ";
    std::cin >> a >> b;
}
