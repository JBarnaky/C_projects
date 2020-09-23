// CA1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <process.h>
#include "..\SP_TASK_08\SPTASK08.h"

//комментарий для подключения библиотеки
#pragma comment(lib,"..\\Debug\\SP_TASK_08.lib")


int main()
{
	int menu=1;
	fflush(stdin);
	setlocale(LC_ALL, "Russian");
	while (menu)
	{
		if (g_nDllFlag == 0)
		{
			system("cls");
			printf("\nВведите значение x: ");
			scanf_s("%d", &g_x);

			printf("\nВведите значение y: ");
			scanf_s("%d", &g_y);

			g_nDllFlag = 1;
		}
		else
		{
			system("cls");
			printf("\n Введенные ранее значения не обработаны");
		}
		printf("\n Для выхода введите 0, любое число для продолжения: ");
		scanf_s("%d", &menu);
	}

	


	printf("\n\n");
	system("pause");
    return 0;
}

