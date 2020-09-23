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
			//������������ �� ��������
			WaitForSingleObject(hTimer, INFINITE);
			uCounter++;
			printf("Open Notepad  %d.\n", uCounter);
			PROCESS_INFORMATION pi; //��������� ��� �������� ���������� � ��������
			STARTUPINFO sti; //��������� ��� �������� ���������� ������� ��������
			ZeroMemory(&sti, sizeof(STARTUPINFO)); //�������� ���� ��������� (������ ������� ���� ���� ������ ������)
			ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
			sti.cb = sizeof(STARTUPINFO);
		
			CreateProcess(NULL, CmdLine, NULL, NULL, 0, 0, NULL, NULL, &sti, &pi);
			HWND hWnd = FindWindow(NULL, L"���������� - �������");
			HWND hWndEdit = FindWindowEx(hWnd, NULL, L"Edit", NULL);
			WCHAR buf[20];
			wsprintf(buf, L"%d", uCounter);
			SendMessage(hWndEdit, WM_SETTEXT, 0, (LPARAM)buf);


			//������������ �� ��������
			WaitForSingleObject(hTimer, INFINITE);
			printf("Close Notepad %d.\n", uCounter);
			DWORD dwExitCode; //���������� ��� �������� ���� ���������� ��������
			if (!GetExitCodeProcess(pi.hProcess, &dwExitCode))  //������� ��������� ���� ���������� ��������
			{   //��������� � ������ ������ ��������
				MessageBox(NULL, TEXT("������ ���������� �������"), TEXT("������"), MB_OK);
			}
			else
			{   //� ������ ������� ��������
				if (dwExitCode == STILL_ACTIVE)  //���������, �������� �� ������� ��� ��� ��� �������������
				{
					TerminateProcess(pi.hProcess, 12); //����� ��������� ������� � ����� ������, ��������� � �������.
				}
				else
				{   //���� ������� ��� ��� �������� - ������������� �� ���� ������������.
					MessageBox(NULL, TEXT("������� ��� ��� ��������"), TEXT("������"), MB_OK);
				}
			}
		}
	}
	getchar();
	return 0;

}
