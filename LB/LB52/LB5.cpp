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
void sumdiag(int, int, int **);

void main()
{
	setlocale(LC_CTYPE, "Russian");

	int i, j, n, m;
	int **A;

	printf("\n Введите количество столбцов: \n");
	scanf("%d", &n);

	printf("\n Введите количество строк: \n");
	scanf("%d", &m);

	if (n == m)
	{
		printf("\n Квадратная матрица (нужна прямоугольная) \n");
		getch();
		exit(0);
	}

	A = (int **) malloc(n*sizeof(int*));
	for (i = 0; i<n; i++)
	{
		*(A+i) = (int *)malloc(m * sizeof(int));
	}

	in(n, m, A);
	out(n, m, A);
	sumdiag(n, m, A);

	for (i = 0; i<n; i++)
		free (*(A + i));
	free (A);

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

void sumdiag(int n, int m, int **a)
{
	int sum = 0;
	int i, j;

		for (i = 0; i < n; i++)
			for (j = i+1; j < m; j++)
				if (i < j)
				{
					sum += fabs(*(*(a + i) + j));
					printf("\n Произведение = %d \n", sum);
				}
}