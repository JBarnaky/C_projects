#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <process.h>
#include <locale.h>

void main()
{
	setlocale(LC_CTYPE, "Russian");

	double a, b, t2;
	
	puts("\n Введите a, b");
	scanf_s("%lf, %lf", &a, &b);

	if ((a == 0) || (b == 0))
	{
		printf("\n Одно или несколько значений = 0 a=%lf, b=%lf \n", a, b);
		fflush(stdin);
			
		puts("\n Введите a, b");
		scanf_s("%lf, %lf", &a, &b);

		if (a * b > 0.5)
		{
			t2 = exp(-1*((fabs(a) + fabs(b)) / 2)) * (cos(a) / sin(a));
			printf("\n Результат 1: t2=%lf \n", t2);
		}

		else 
		{
			if (0.4 < a * b <= 0.5);
			t2 = fabs(a + (pow(b, 2))) * (cos(b) / sin(b));
			printf("\n Результат 2: t2=%lf \n", t2);
		}
	}
	else
	{
		if (a * b > 0.5)
		{
			t2 = exp(-1*((fabs(a) + fabs(b)) / 2)) * (cos(a) / sin(a));
			printf("\n Результат 1: t2=%lf \n", t2);
		}

		else
		{
			if (0.4 < a * b <= 0.5);
			t2 = fabs(a + (pow(b, 2))) * (cos(b) / sin(b));
			printf("\n Результат 2: t2=%lf \n", t2);
		}
	}
	_getch();
}