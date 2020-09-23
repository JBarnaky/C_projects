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
	int nom; //����� ������
	WCHAR path[50]; //���� � �����
	int nNumb; //���������� ���� � �����
	double sum; //����� � �����
	HANDLE hPort; //���� ����� ������
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
			puts("������ �������� �������");
			getch();
		}
	}
	double AllSum = 0;
	double nAllNumb = 0;
	DWORD res = WaitForMultipleObjects(4, hThreads, TRUE, INFINITE); //��� ��������� ���� �������
	for (int i = 0; i<4; i++) //������� ����� ����� + ����� ����������� ������� �����
	{
		AllSum += Param[i].sum;
		nAllNumb += Param[i].nNumb;
		printf("���� �%d   ����� �����: %.0lf   ������� ��������: %lf\n", i, Param[i].sum, Param[i].sum / Param[i].nNumb);
	}
	printf("������� ��������: %lf\n", AllSum / nAllNumb);
	DWORD FinishTime = GetTickCount();
	printf("����� ������ ���������: %d", FinishTime - StartTime);
	getch();
	return 0;
}

DWORD WINAPI ThreadFunction(PVOID pvParam)
{
	THREAD_PARAM* lpParam = (THREAD_PARAM*)pvParam;

	HANDLE hFile = CreateFile(lpParam->path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"������ �������� �����", NULL, MB_OK);
		return 1;
	}
	lpParam->nNumb = GetFileSize(hFile, NULL) / 4;
	int* BufOfNumb = (int*)calloc(lpParam->nNumb, sizeof(int));
	if (BufOfNumb == NULL)
	{
		MessageBox(NULL, L"������. �������� ������", NULL, MB_OK);
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
	} while (FinishNom != lpParam->nom);//��� ���������� �� ��������� ����� ������� ������
	for (int n = 0; n<lpParam->nNumb; n++)
	{
		lpParam->sum += BufOfNumb[n];
	}
	free(BufOfNumb);
	return 0;//�������� ����������
}

