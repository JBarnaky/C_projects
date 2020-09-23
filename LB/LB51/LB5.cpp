#include <stdio.h>      
#include <conio.h>     
#include <process.h>   
#include <locale.h>     
#include <malloc.h>    
#include <windows.h>   
#include <stdlib.h>
#include <math.h>

void in(int, int, int **);
void out(int, int, int **);
void pdiag(int, int, int **);

void main()
{
	setlocale(LC_CTYPE, "Russian");

	int i, j, n, m;
	int **A;

	printf("\n Введите количество столбцов: \n");
	scanf("%d", &n);

	printf("\n Введите количество строк: \n");
	scanf("%d", &m);

	A = new int *[n];
	for (i = 0; i<n; i++)
	{
		*(A + i) = new int[n];
	}

	in(n, m, A);
	out(n, m, A);
	pdiag(n, m, A);

	for (i = 0; i<n; i++)
		delete[](*(A + i));
	delete[] A;

	getch();
}

void in(int n, int m, int **a)
{
	int i, j;
	for (i = 0; i<n; i++)
		for (j = 0; j<m; j++)
		{
			printf("\n a [%d][%d]= ", i, j);
			scanf("%d", &*(*(a + i) + j));
		}
}


void out(int n, int m, int **a)
{
	int i, j;
	for (i = 0; i<n; i++)
	{
		printf("\n");
		for (j = 0; j<m; j++)
			printf("%d \t ", *(*(a + i) + j));
	}
}

void pdiag(int n, int m, int **a)
{
	int s = 1;
	int i;
	if (n == m)
	{
		for (i = 0; i < n; i++)
			s *= *(*(a + i) + i);
		printf("\n Произведение = %d \n", s);
	}
}