#include "targetver.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD StartTime = GetTickCount();
	setlocale(LC_ALL, "RUSSIAN");
	HANDLE hFiles[4] = { 0 };
	int nNumb[4] = { 0 };
	OVERLAPPED ov[4] = { 0 };
	HANDLE hEvents[4] = { 0 };
	int* BufOfNumb[4];

	for (int i = 0; i<4; i++)
	{
		WCHAR Buf[100];
		wsprintf(Buf, L"C:\\SP_2.6\\SP_2.6\\File%d", i);
		hFiles[i] = CreateFile(Buf, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
		if (hFiles[i] == INVALID_HANDLE_VALUE)
		{
			puts("Ошибка открытия файлов");
			getch();
			return 1;
		}
		nNumb[i] = GetFileSize(hFiles[i], NULL) / 4;
		BufOfNumb[i] = (int*)calloc(nNumb[i], sizeof(int));
		if (BufOfNumb == NULL)
		{
			puts("Ошибка. Нехватка памяти");
			getch();
			return 1;
		}
		hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		ov[i].hEvent = hEvents[i];
		ov[i].OffsetHigh = 0;
		ov[i].Offset = 0;
		DWORD nNumbOfBytes;
		ReadFile(hFiles[i], BufOfNumb[i], nNumb[i], &nNumbOfBytes, &ov[i]); //асинхронное чтение файлов
	}
	double AllSum = 0;
	double nAllNumb = nNumb[0] + nNumb[1] + nNumb[2] + nNumb[3];

	for (int i = 0; i<4; i++) //4ре раза должны получить результат от 4ёх чтений
	{
		DWORD res = WaitForMultipleObjects(4, hEvents, FALSE, INFINITE); //ждём любое событие
		int posRes = (int)(res - WAIT_OBJECT_0);
		double sum = 0;
		for (int n = 0; n<nNumb[posRes]; n++)
		{
			sum += BufOfNumb[posRes][n];
		}
		AllSum += sum;
		printf("Файл №%d   Сумма чисел: %.0lf   Среднее значение: %lf\n", posRes, sum, sum / nNumb[posRes]);
	}
	free(BufOfNumb);
	printf("Среднее значение: %lf\n", AllSum / nAllNumb);
	DWORD FinishTime = GetTickCount();
	printf("Время работы программы: %d", FinishTime - StartTime);
	getch();
	return 0;
}

