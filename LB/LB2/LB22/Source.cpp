#include <iostream>
#include <cmath>
#include <locale>
#include <clocale>
#include <conio.h>

int main() {
    std::setlocale(LC_CTYPE, "Russian");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());

    double x, y, z, h;

    x = 2.444;
    y = 0.869 * std::pow(10, -2);
    z = -0.13 * std::pow(10, 3);

    // Calculate h
    h = std::pow(x, (y + 1)) + std::exp(y - 1) / (1 + x * std::fabs(y - std::tan(z)) * (1 + std::fabs(y - x)) + std::pow(std::fabs(y - x), 2) / 2 - std::pow(std::fabs(y - x), 3) / 3);

    // Output the result
    std::cout << "\nРезультат: h=" << std::fixed << std::setprecision(6) << h << std::endl;

    // Wait for a key press before closing
    _getch();

    return 0;
}
