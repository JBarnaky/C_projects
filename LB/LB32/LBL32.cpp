#include <stdio.h>
#include <conio.h> 
#include <math.h>
#include <process.h>
#include <locale.h>

//double funS(int, double);
//double funY(double);
double funS(int, double *);
double funY(double &);
void main ()
{	
	setlocale(LC_CTYPE, "Russian");

	double a,b,h,x,y,s,delta;
	double *x1;
	x1 = &x;
	int n,k;

	printf("¬ведите a:");
	scanf_s("%lf", &a);

	printf("¬ведите b:");
	scanf_s("%lf", &b);

	printf("¬ведите h:");
	scanf_s("%lf", &h);

	printf("¬ведите n:");
	scanf_s("%d", &n);

	printf("\n");
	puts("| x | Y(x) | S(x) | Y(x)-S(x) |");
	puts("_______________________________\n");

	x=a;
	while (x<=b)
	{
		s = 0;
		for(k=1;k<=n;k++);
		{
			//s+=funS(k,x);
			s += funS(k, &x);
		}
			//y=funY(x);
			y = funY(x);
			delta=fabs(y-s);
			printf("x=%.2lf | y=%.5lf | s=%.5lf| delta=%.5lf | \n", x, y, s, delta);
			x+=h;
		}
		_getch();
}
/*double funS(int k, double x)
{
return pow(-1., k + 1)*pow(x, 2.*k) / (2.*k*(2.*k - 1));
}
double funY(double x)
{
return (x*atan(x) - log(sqrt(1 + pow(x, 2))));
}*/

double funS( int k, double *x1)
{
	return pow(-1.,k+1)*pow(*x1,2.*k)/(2.*k*(2.*k-1));
}
double funY(double &x)
{
	return (x*atan(x)-log(sqrt(1+pow(x,2))));
}
