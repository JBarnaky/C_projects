#include <iostream>
#include <cmath>
#include <locale>
#include <conio.h>

void f1(double, double, double);

int main() {
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());

    double x, y, z, u;
    double min, max1, max2, max3;

    std::cout << "Введите x, y, z: ";
    std::cin >> x >> y >> z;

    if ((x == y) || (x == z) || (z == y)) {
        f1(x, y, z);
    }

    min = std::min(y, z);
    max1 = std::max(x, y);
    max2 = std::max(y, z);
    max3 = std::max(max1, max2);

    u = min / max3;

    std::cout << "\n Результат: u=" << std::fixed << std::setprecision(6) << u << std::endl;

    _getch();

    return 0;
}

void f1(double x, double y, double z) {
    std::cout << "\n Введены одинаковые значения x=" << x << ", y=" << y << ", z=" << z << " повторите ввод \n";

    std::cout << "\n Введите x, y, z: ";
    std::cin >> x >> y >> z;
}
