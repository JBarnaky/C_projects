// CA2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <process.h>
#include "..\SP_TASK_08\SPTASK08.h"

//����������� ��� ����������� ����������
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
			printf("\n�������� x: %d", g_x);
			printf("\n�������� y: %d", g_y);
			
			printf("\n\n�����     : %d", add());
			printf("\n��������    : %d", sub());
			printf("\n������������: %d", mult());
			printf("\n�������     : %d", div());
			g_nDllFlag = 0;
		}
		else
		{
			system("cls");
			printf("\n �������� ��� ������� �� ������������");
		}
		printf("\n\n ��� ������ ������� 0, ����� ����� ��� �����������: ");
		scanf_s("%d", &menu);
	}




	printf("\n\n");
	system("pause");
    return 0;
}

