#include <stdio.h>
#include <conio.h> 
#include <math.h>
#include <process.h>
#include <locale.h>


void main ()
{	
	setlocale(LC_CTYPE, "Russian");

	double a,b,h,x,y,s,delta;
	int n,k;

	printf("������� a:");
	scanf_s("%lf", &a);

	printf("������� b:");
	scanf_s("%lf", &b);

	printf("������� h:");
	scanf_s("%lf", &h);

	printf("������� n:");
	scanf_s("%d", &n);

	printf("\n");
	puts("| x | Y(x) | S(x) | Y(x)-S(x) |");
	puts("_______________________________\n");

	x=a;
	while (x<=b)
	{
		s=0;
		for(k=1;k<=n;k++);
		{
			s+=pow(-1.,k+1)*pow(x,2.*k)/(2.*k*(2.*k-1));
		}
			y=x*atan(x)-log(sqrt(1+pow(x,2)));
			delta=fabs(y-s);
			printf("x=%.2lf | y=%.5lf | s=%.5lf| delta=%.5lf | \n", x, y, s, delta);
			x+=h;
		}
		_getch();
	}