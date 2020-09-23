#include "targetver.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <tchar.h>

DWORD WINAPI ThreadFunction(PVOID);

struct THREAD_PARAM
{
	int nom; //номер потока
	WCHAR path[50]; //путь к файлу
	int nNumb; //количество цифр в файле
	double sum; //сумма в файле
	HANDLE hPort; //порт ввода вывода
};

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD StartTime = GetTickCount();
	setlocale(LC_ALL, "RUSSIAN");
	HANDLE hFiles[4] = { 0 };
	int nNumb[4] = { 0 };
	OVERLAPPED ov[4] = { 0 };
	HANDLE hEvents[4] = { 0 };
	HANDLE hThreads[4] = { 0 };
	THREAD_PARAM Param[4] = { 0 };
	HANDLE hPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);

	for (int i = 0; i<4; i++)
	{
		wsprintf(Param[i].path, L"C:\\SP_2.6\\SP_2.6\\File%d", i);
		Param[i].hPort = hPort;
		Param[i].nom = i;
		hThreads[i] = CreateThread(NULL, 0, ThreadFunction, &Param[i], 0, NULL);
		if (hThreads[i] == NULL)
		{
			puts("Ошибка создания потоков");
			getch();
		}
	}
	double AllSum = 0;
	double nAllNumb = 0;
	DWORD res = WaitForMultipleObjects(4, hThreads, TRUE, INFINITE); //ждём отработку всех потоков
	for (int i = 0; i<4; i++) //находим общую сумму + вывод результатов каждого файла
	{
		AllSum += Param[i].sum;
		nAllNumb += Param[i].nNumb;
		printf("Файл №%d   Сумма чисел: %.0lf   Среднее значение: %lf\n", i, Param[i].sum, Param[i].sum / Param[i].nNumb);
	}
	printf("Среднее значение: %lf\n", AllSum / nAllNumb);
	DWORD FinishTime = GetTickCount();
	printf("Время работы программы: %d", FinishTime - StartTime);
	getch();
	return 0;
}

DWORD WINAPI ThreadFunction(PVOID pvParam)
{
	THREAD_PARAM* lpParam = (THREAD_PARAM*)pvParam;

	HANDLE hFile = CreateFile(lpParam->path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Ошибка открытия файла", NULL, MB_OK);
		return 1;
	}
	lpParam->nNumb = GetFileSize(hFile, NULL) / 4;
	int* BufOfNumb = (int*)calloc(lpParam->nNumb, sizeof(int));
	if (BufOfNumb == NULL)
	{
		MessageBox(NULL, L"Ошибка. Нехватка памяти", NULL, MB_OK);
		return 1;
	}
	//hEvents[i]=CreateEvent(NULL,FALSE,FALSE,NULL);
	CreateIoCompletionPort(hFile, lpParam->hPort, lpParam->nom, 0);
	OVERLAPPED ov = { 0 };
	ov.hEvent = NULL;
	ov.OffsetHigh = 0;
	ov.Offset = 0;
	DWORD nNumbOfBytes;
	ReadFile(hFile, BufOfNumb, lpParam->nNumb, &nNumbOfBytes, &ov);
	DWORD FinishNom;
	LPOVERLAPPED OvRes;
	do
	{
		GetQueuedCompletionStatus(lpParam->hPort, &nNumbOfBytes, &FinishNom, &OvRes, INFINITE);
	} while (FinishNom != lpParam->nom);//жду оповещение об обработке файла данного потока
	for (int n = 0; n<lpParam->nNumb; n++)
	{
		lpParam->sum += BufOfNumb[n];
	}
	free(BufOfNumb);
	return 0;//успешное выполнение
}

