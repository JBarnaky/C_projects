#include <iostream>
#include <iomanip>
#include <cmath>
#include <locale>

// Function prototypes
double funS(double s, int k, double x);
double funY(double y, double x);

int main() {
    // Set locale to Russian
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());

    double a, b, h, x, y, s, delta;
    int n;

    // Input values
    std::cout << "Введите a: ";
    std::cin >> a;

    std::cout << "Введите b: ";
    std::cin >> b;

    std::cout << "Введите h: ";
    std::cin >> h;

    std::cout << "Введите n: ";
    std::cin >> n;

    std::cout << "\n";
    std::cout << "| x | Y(x) | S(x) | Y(x)-S(x) |\n";
    std::cout << "_______________________________\n";

    x = a;
    while (x <= b) {
        s = 0.0;
        y = 0.0;
        for (int k = 1; k <= n; k++) {
            s = funS(s, k, x);
        }
        y = funY(y, x);
        delta = std::fabs(y - s);

        std::cout << "x=" << std::fixed << std::setprecision(2) << x
                  << " | y=" << std::fixed << std::setprecision(5) << y
                  << " | s=" << std::fixed << std::setprecision(5) << s
                  << " | delta=" << std::fixed << std::setprecision(5) << delta
                  << " |\n";

        x += h;
    }

    std::cin.get();
    return 0;
}

double funS(double s, int k, double x) {
    s += std::pow(-1.0, k + 1) * std::pow(x, 2.0 * k) / (2.0 * k * (2.0 * k - 1));
    return s;
}

double funY(double y, double x) {
    y += x * std::atan(x) - std::log(std::sqrt(1.0 + std::pow(x, 2.0)));
    return y;
}
