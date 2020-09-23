// Yatsk_2_3_timer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _WIN32_WINDOWS 0x0410 
#define WINVER 0x0400

#include <windows.h>
#include <stdio.h>


int _tmain(int argc, _TCHAR* argv[])
{
	UINT uCounter = 0;
	HANDLE hTimer;
	LARGE_INTEGER li;
	HANDLE hProcess;
	TCHAR CmdLine[24];

	wsprintf(CmdLine, TEXT("NOTEPAD.EXE"));
	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	li.QuadPart = -(15 * 10000000);

	if (SetWaitableTimer(hTimer, &li, 10 * 1000, NULL, NULL, FALSE))
	{
		while (TRUE)
		{
			//Срабатывание на открытие
			WaitForSingleObject(hTimer, INFINITE);
			uCounter++;
			printf("Open Notepad  %d.\n", uCounter);
			PROCESS_INFORMATION pi; //Структура дял хранения информации о процессе
			STARTUPINFO sti; //Структура для хранения информации запуска процесса
			ZeroMemory(&sti, sizeof(STARTUPINFO)); //Обнуляет поля структуры (просто забиает весь блок памяти нулями)
			ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
			sti.cb = sizeof(STARTUPINFO);
		
			CreateProcess(NULL, CmdLine, NULL, NULL, 0, 0, NULL, NULL, &sti, &pi);
			HWND hWnd = FindWindow(NULL, L"Безымянный - Блокнот");
			HWND hWndEdit = FindWindowEx(hWnd, NULL, L"Edit", NULL);
			WCHAR buf[20];
			wsprintf(buf, L"%d", uCounter);
			SendMessage(hWndEdit, WM_SETTEXT, 0, (LPARAM)buf);


			//Срабатывание на закрытие
			WaitForSingleObject(hTimer, INFINITE);
			printf("Close Notepad %d.\n", uCounter);
			DWORD dwExitCode; //Переменная для хранения кода завершения процесса
			if (!GetExitCodeProcess(pi.hProcess, &dwExitCode))  //Попытка получения кода завершения процесса
			{   //Сообщение в случае ошибки проверки
				MessageBox(NULL, TEXT("Ошибка выполнения запроса"), TEXT("Ошибка"), MB_OK);
			}
			else
			{   //В случае удачной проверки
				if (dwExitCode == STILL_ACTIVE)  //Проверяем, завершен ли процесс или все еще функционирует
				{
					TerminateProcess(pi.hProcess, 12); //Грубо прерываем процесс с кодом выхода, указанным в задании.
				}
				else
				{   //Если процесс уже был завершен - предупреждаем об этом пользователя.
					MessageBox(NULL, TEXT("Процесс уже был завершен"), TEXT("Ошибка"), MB_OK);
				}
			}
		}
	}
	getchar();
	return 0;

}
