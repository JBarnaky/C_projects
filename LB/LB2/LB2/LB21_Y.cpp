#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE, "Russian");

    double b;

    puts("Введите b:");
    scanf("%lf", &b);

    double temp = sqrt(pow(b, 2) - 4) + b + 2;
    double z1 = sqrt(2 * b + 2 * temp) / temp;
    double z2 = 1 / sqrt(b + 2);

    printf("Результат: z1=%.4lf z2=%.4lf\n", z1, z2);

    return 0;
}
