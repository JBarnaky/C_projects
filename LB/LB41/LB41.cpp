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
	int i;
	int max = 0;
	int pm;

	for (i = 0; i<n; ++i)
	{
		if (Arr[i] > max)
		{
			max = Arr[i];
			pm = i;
		}
	}
	int sum = 0;
	for (i = 0; i<pm; ++i)
	{
		if ((Arr[i]>0) && (Arr[i]<max))
		sum += Arr[i];
	}
	printf("\n Сумма + элементов массива, расположенных до max элемента %d = %d\n", Arr[pm], sum);
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
