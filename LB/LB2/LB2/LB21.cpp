#include <iostream>
#include <cmath>
#include <locale>

int main() {
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());

    double x = 2.444;
    double y = 0.869 * std::pow(10, -2);
    double z = -0.13 * std::pow(10, 3);

    // Calculate h
    double h = std::pow(x, y + 1) + std::exp(y - 1) / (1 + x * (std::fabs(y - std::tan(y))) * (1 + std::fabs(y - x)) + std::pow(std::fabs(y - x), 2) / 2 - std::pow(std::fabs(y - x), 3) / 3);

    // Output the result
    std::cout << "\nРезультат: h=" << std::fixed << std::setprecision(4) << h << std::endl;

    return 0;
}
