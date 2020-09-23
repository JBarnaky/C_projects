#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <locale.h>

void f1(double, double);
void main()
{
	setlocale(LC_CTYPE, "Russian");

	double x, y, z;

	puts("Введите x, z");

	scanf_s("%lf, %lf", &x, &z);

	if ((x == 0) || (z == 0))  f1(x, z);

	y = x*(sin(x) + exp(-(x + 3)));
	
	if (z > 0)
	{
		x = -3 * z;
		printf("\n Результат 1: x=%lf y=%lf ", x, y);
	}
	if (z <= 0)
	{
		x = pow(z, 2);
		printf("\n Результат 2: x=%lf y=%lf ", x, y);
	}
			
		_getch();
	}

void f1(double x, double z)
{
	printf("\n Нет решения x=%lf, z=%lf  \n", x, z);
	fflush(stdin);

	puts("\n Введите x, z");

	scanf_s("%lf, %lf", &x, &z);

}