#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <locale.h>

void main()
{
	setlocale(LC_CTYPE, "Russian");

	double x, y, z, h;

	x = 2.444;
	y = 0.869*pow(10, -2);
	z = -0.13*pow(10, 3);
	// h = -0.49871;

	h = pow(x, (y + 1)) + exp(y - 1) / 1 + x*(fabs(y - tan(z)))*(1 + fabs(y - x)) + pow(fabs(y - x), 2) / 2 - pow(fabs(y - x), 3) / 3;
	
	printf("\n Результат: h=%lf \n", h);

	_getch();
}