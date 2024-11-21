#include <iostream>
#include <cmath>
#include <locale>
#include <conio.h>

void f1(double, double);

int main() {
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());

    double x, y, z;

    std::cout << "Введите x, z: ";
    std::cin >> x >> z;

    if ((x == 0) || (z == 0)) {
        f1(x, z);
    }

    y = x * (std::sin(x) + std::exp(-(x + 3)));

    if (z > 0) {
        x = -3 * z;
        std::cout << "\n Результат 1: x=" << std::fixed << std::setprecision(6) << x << " y=" << y << std::endl;
    }
    if (z <= 0) {
        x = std::pow(z, 2);
        std::cout << "\n Результат 2: x=" << std::fixed << std::setprecision(6) << x << " y=" << y << std::endl;
    }

    _getch();

    return 0;
}

void f1(double x, double z) {
    std::cout << "\n Введены нулевые значения x=" << x << ", z=" << z << std::endl;

    std::cout << "\n Введите x, z: ";
    std::cin >> x >> z;
}
