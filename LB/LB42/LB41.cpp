#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <process.h>
#include <locale.h>
#include <malloc.h>
#include <stdlib.h>

void read(int*Arr, int n)
{
	for (int i=0; i<n; i++)
	{
		printf("Введите значение элемента [%d]:\n",i);
		scanf("%d",(Arr+i));
	}
}
void write(int*Arr, int n)
{
	for (int i=0; i<n; i++)
	{
		printf("%p = %d ",(Arr+i),*(Arr+i));
		printf("[%d]\n",i);
	}
}
void Fmax(int*Arr, int n)
{
	int pf;
	int i = 0;
	int max = Arr[i];
	for (i = 0; i<n; i++)
	{
		if (Arr[i]>0)
		{
			max = Arr[i];
			pf = i;
		}
	}
	int S = 0;
	for (i = 0; i<pf; i++)
	{
		if (Arr[i]>0)
		S += Arr[i];
	}
	printf("\n Сумма + элементов массива, расположенных до max элемента %.d=%d\n", Arr[pf], S);
}

void main()
{
	setlocale(LC_CTYPE, "Russian");
	int *A, M;

	printf("Введите размерность массива M:");
	scanf("%d", &M);

	A = new int[M];

	printf("\n Массив A:\n");
	read(A, M);
	write(A, M);
	Fmax(A, M);

	delete[]A;
	getch();
}
