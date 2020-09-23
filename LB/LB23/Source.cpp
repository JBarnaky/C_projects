#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <locale.h>

void main()
{
	setlocale(LC_CTYPE, "Russian");

	double x, y, z;

	puts("Введите z");
	scanf_s("%lf", &z);

	if (z > 0) x = -3 * z;
			
		y = x*(sin(x) + (exp(x+3)*-1));
		printf("\n Результат 1: y=%lf ", y);
	
	if (z <= 0) x = pow(z, 2);

		y = x*(sin(x) + (exp(x+3)*-1));
		printf("\n Результат 2: y=%lf ", y);
			
	_getch();
}