#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <process.h>
#include <locale.h>

void f1(double, double, double);
void main()
{
	setlocale(LC_CTYPE, "Russian");

	double x, y, z, u;
	double min, max1, max2, max3;

	puts("¬ведите x, y, z");

	scanf_s("%lf, %lf, %lf", &x, &y, &z);

	if ((x == y) || (x == z) || (z == y)) f1(x, y, z);

	if (y > z) min = z;
	else min = y;

	if (x > y) max1 = x;
	else max1 = y;

	if (y > z) max2 = y;
	else max2 = z;

	if (max1 > max2) max3 = max1;
	else max3 = max2;

	u = min / max3;
	
	printf("\n –езультат: u=%lf \n", u);
	
	_getch();
}

void f1(double x, double y, double z)
{
	printf("\n ќдно или несколько значений x=%lf, y=%lf, z=%lf совпадают \n", x, y, z);
	fflush(stdin);

	puts("\n ¬ведите x, y, z");

	scanf_s("%lf, %lf, %lf", &x, &y, &z);

}