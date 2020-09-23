// Yatsk_DLL_I.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "targetver.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include "..\Yatsk_DLL\Yatsk_DLL.h"

//int g_nDllCallsCount=1;


int _tmain(int argc, _TCHAR* argv[])
{
	int x = 0;
	int y = 0;
	int z = 0;
	// Fun121
	printf("int Fun121(double, double)\nEnter x\n");
	scanf_s("%d", &x);
	printf("Enter y\n");
	scanf_s("%d", &y);
	int rez = Fun121(x, y);
	g_nFnCallsCount++;
	wprintf(TEXT("Result: %d; g_nFnCallsCount = %d; g_nDllCallsCount = %d"), rez, g_nFnCallsCount, g_nDllCallsCount);
	// Fun122
	printf("\nfloat Fun122(int, int, int) \nEnter x\n");
	scanf_s("%d", &x);
	printf("Enter y\n");
	scanf_s("%d", &y);
	printf("Enter z\n");
	scanf_s("%d", &z);
	float rez1 = Fun122(x, y, z);
	g_nFnCallsCount++;
	wprintf(TEXT("Result: %d; g_nFnCallsCount = %d; g_nDllCallsCount = %d"), rez1, g_nFnCallsCount, g_nDllCallsCount);
	// Fun123
	printf("\nvoid Fun123(int, int *)\nEnter x\n");
	scanf_s("%d", &x);
	int y2 = 0;
	g_nFnCallsCount++;
	Fun123(x, &y2);
	wprintf(TEXT("Result: %d; g_nFnCallsCount = %d; g_nDllCallsCount = %d"), y2, g_nFnCallsCount, g_nDllCallsCount);



	getchar();
	return 0;

}

