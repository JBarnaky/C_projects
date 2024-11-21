#include <iostream>
#include <cmath>
#include <locale>
#include <limits>

double funS(int k, double x);
double funY(double x);

int main() {
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
        for (k = 1; k <= n; k++) {
            s += funS(k, x);
        }
        y = funY(x);
        delta = std::fabs(y - s);
        std::cout << "x=" << std::fixed << std::setprecision(2) << x
                  << " | y=" << std::fixed << std::setprecision(5) << y
                  << " | s=" << std::fixed << std::setprecision(5) << s
                  << " | delta=" << std::fixed << std::setprecision(5) << delta
                  << " | \n";
        x += h;
    }

    std::cin.get(); // Pause the program
    return 0;
}

double funS(int k, double x) {
    return std::pow(-1.0, k + 1) * std::pow(x, 2.0 * k) / (2.0 * k * (2.0 * k - 1));
}

double funY(double x) {
    return x * std::atan(x) - std::log(std::sqrt(1 + std::pow(x, 2)));
}
