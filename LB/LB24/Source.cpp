#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <process.h>
#include <locale.h>

void main()
{
	setlocale(LC_CTYPE, "Russian");

	double x, y, z, u;
	double min, max1, max2, max;

	puts("\n ������� x, y, z");
	
	scanf_s("%lf, %lf, %lf", &x, &y, &z);

	if ((x == y) || (x == z) || (z == y))
	{
		printf("\n ���� ��� ��������� �������� ��������� x=%lf, y=%lf, z=%lf \n", x, y, z);
		fflush(stdin);

		puts("\n ������� x, y, z");
		scanf_s("%lf, %lf, %lf", &x, &y, &z);
			
			if (y > z) min = z;
			else min = y;

			if ((y == 0) || (z == 0)) printf("\n ������� �� 0");
									
			if (x > y) max1 = x;
			else max1 = y;
			
			if (y > z) max2 = y;
			else max2 = z;
			
			if (max1 > max2) max = max1;
			else max = max2;
			
			u = min / max;
			printf("\n ���������: u=%lf \n", u);

			_getch();
	}
	else
	{
		if (y > z) min = z;
		else min = y;

		if ((y == 0) || (z == 0)) printf("\n ������� �� 0");
						
		if (x > y) max1 = x;
		else max1 = y;
		
		if (y > z) max2 = y;
		else max2 = z;
		
		if (max1 > max2) max = max1;
		else max = max2;
		
		u = min / max;
		printf("\n ���������: u=%lf \n", u);
			
		_getch();
	}
}