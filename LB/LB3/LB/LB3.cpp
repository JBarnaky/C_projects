#include <iostream>
#include <cmath>
#include <locale>
#include <limits>

void main() {
    std::locale::global(std::locale("Russian_Russia.1251")); // Set locale to Russian
    std::cout.imbue(std::locale()); // Apply locale to cout

    double a, b, h, x, y, s, delta;
    int n, k;

    std::cout << "Введите a: ";
    std::cin >> a;

    std::cout << "Введите b: ";
    std::cin >> b;

    std::cout << "Введите h: ";
    std::cin >> h;

    std::cout << "Введите n: ";
    std::cin >> n;

    std::cout << "\n";
    std::cout << "| x | Y(x) | S(x) | Y(x)-S(x) |" << std::endl;
    std::cout << "_______________________________\n";

    x = a;
    while (x <= b) {
        s = 0;
        for (k =1; k <= n; k++) {
            s += std::pow(-1.0, k + 1) * std::pow(x, 2.0 * k) / (2.0 * k * (2.0 * k - 1));
        }
        y = x * std::atan(x) - std::log(std::sqrt(1 + std::pow(x, 2)));
        delta = std::fabs(y - s);
        std::cout << "x=%.2lf | y=%.5lf | s=%.5lf | delta=%.5lf | \n", x, y, s, delta;
        x += h;
    }

    std::cin.get(); // Pause the program
    return 0;
}
