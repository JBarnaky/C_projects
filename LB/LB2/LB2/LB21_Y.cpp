#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <locale.h>

void main()
	{
		setlocale(LC_CTYPE, "Russian");

		double z1, z2, b;
		
		puts("Введите b");

		scanf_s("%lf", &b);

		z1=(sqrt(2*b+2*(sqrt(pow(b,2)-4))))/((sqrt(pow(b,2)-4)+b+2));
		z2=1/(sqrt(b+2));
		
		printf("\n Результат: z1=%.4lf z2=%.4lf\n", z1, z2);
		_getch();
	}