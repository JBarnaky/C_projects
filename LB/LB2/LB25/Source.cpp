#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <process.h>
#include <locale.h>

void f1(double, double);
void main()
{
	setlocale(LC_CTYPE, "Russian");

	double a, b, t2;
	
	puts("Введите a, b");

	scanf_s("%lf, %lf", &a, &b);

	if ((a == 0) || (b == 0))  f1(a, b);

	if (a * b > 0.5)
	{
		t2 = exp(-((fabs(a) + fabs(b)) / 2)) * (1 / tan(a));
		printf("\n Результат 1: t2=%lf \n", t2);
	}
	
		if (0.4 < a * b <= 0.5)
		{
			t2 = fabs(a + (pow(b, 2))) * (1 / tan(b));
			printf("\n Результат 2: t2=%lf \n", t2);
		}
		
	_getch();
}

void f1(double a, double b)
{
	printf("\n Нет решения a=%lf, b=%lf  \n", a, b);
	fflush(stdin);

	puts("\n Введите a, b");

	scanf_s("%lf, %lf", &a, &b);

}