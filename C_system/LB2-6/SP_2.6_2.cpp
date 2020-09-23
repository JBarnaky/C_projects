// SP_2.6_2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SP_2.6_2.h"
#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <conio.h>

#include <time.h>
#include <Windows.h>
#include <tchar.h>

int _WinMain(int argc, _TCHAR* argv[])
{
	DWORD StartTime = GetTickCount();
	setlocale(LC_ALL, "RUSSIAN");
	double AllSum = 0;
	double nAllNumb = 0;
	for (int i = 0; i<4; i++)
	{
		WCHAR Buf[100];
		wsprintf(Buf, L"C:\\SP_2.6_2\\SP_2.6_2\\File%d", i);
		HANDLE hFile = CreateFile(Buf, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			puts("Ошибка открытия файлов");
			_getch();
			return 1;
		}
		int nNumb = GetFileSize(hFile, NULL) / 4;
		int* BufOfNumb = (int*)calloc(nNumb, sizeof(int));
		if (BufOfNumb == NULL)
		{
			puts("Ошибка. Нехватка памяти");
			_getch();
			return 1;
		}
		DWORD nReadBytes;
		ReadFile(hFile, BufOfNumb, nNumb, &nReadBytes, NULL);
		double sum = 0;
		for (int n = 0; n<nNumb; n++)
		{
			sum += BufOfNumb[n];
		}
		free(BufOfNumb);

		printf("Файл №%d   Сумма чисел: %.0lf   Среднее значение: %lf\n", i, sum, sum / nNumb);
		AllSum += sum;
		nAllNumb += nNumb;
	}
	printf("Среднее значение: %lf\n", AllSum / nAllNumb);
	DWORD FinishTime = GetTickCount();
	printf("Время работы программы: %d", FinishTime - StartTime);
	_getch();
	return 0;
}
