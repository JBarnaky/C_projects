// CA2.cpp : Defines the entry point for the console application.
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
	int menu = 1;
	fflush(stdin);
	setlocale(LC_ALL, "Russian");
	while (menu)
	{
		if (g_nDllFlag == 1)
		{
			system("cls");
			printf("\nЗначение x: %d", g_x);
			printf("\nЗначение y: %d", g_y);
			
			printf("\n\nСумма     : %d", add());
			printf("\nРазность    : %d", sub());
			printf("\nПроизведение: %d", mult());
			printf("\nЧастное     : %d", div());
			g_nDllFlag = 0;
		}
		else
		{
			system("cls");
			printf("\n Значения для функций не установленны");
		}
		printf("\n\n Для выхода введите 0, любое число для продолжения: ");
		scanf_s("%d", &menu);
	}




	printf("\n\n");
	system("pause");
    return 0;
}

