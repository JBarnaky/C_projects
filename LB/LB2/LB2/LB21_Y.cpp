#include <iostream>
#include <cmath>
#include <locale>

int main() {
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());

    double b;

    std::cout << "Введите b: ";
    std::cin >> b;

    double temp = std::sqrt(std::pow(b, 2) - 4) + b + 2;
    double z1 = std::sqrt(2 * b + 2 * temp) / temp;
    double z2 = 1 / std::sqrt(b + 2);

    std::cout << "Результат: z1=" << std::fixed << std::setprecision(4) << z1 << " z2=" << z2 << std::endl;

    return 0;
}
