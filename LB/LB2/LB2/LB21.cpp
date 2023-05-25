#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE, "Russian");

    double x = 2.444;
    double y = 0.869 * pow(10, -2);
    double z = -0.13 * pow(10, 3);

    double h = pow(x, y + 1) + exp(y - 1) / (1 + x * (fabs(y - tan(y))) * (1 + fabs(y - x)) + pow(fabs(y - x), 2) / 2 - pow(fabs(y - x), 3) / 3);

    printf("\nДåçóëüòàò: h=%.4lf\n", h);

    return 0;
}
