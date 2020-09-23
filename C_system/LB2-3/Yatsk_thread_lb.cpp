// Yatsk_thread_lb.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Yatsk_thread_lb.h"
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h> 


// Global Variables:
int g_uThCount = 0;
HANDLE		hSecThread[4];         
HWND		hWnd;         
HINSTANCE	g_hInst;              
DWORD		dwSecThreadID[4];        

UINT threadPriority[3];    // приориет потока
DWORD dwExitCode[4];
UINT nPriotity[2] = { 0, 0 };
HWND hPictureControl;   // окно для вывода изображения
UINT imageID = 130;

BOOL		bTerminate = FALSE; // TRUE to quit
BOOL		bUseMutex = FALSE;  // TRUE to make one thread draw at a time
HANDLE		hDrawMutex;

struct THREAD_PARAM // структура для передачи в функцию потока
{
	int threadNum;
	int xPos;
	int yPos;
	HWND hWnd;
};


THREAD_PARAM ThrParam1;
THREAD_PARAM ThrParam2; 

DWORD WINAPI ThreadFunc1(PVOID pvParam);
DWORD WINAPI ThreadFunc2(PVOID pvParam);
DWORD WINAPI ThreadFunc3(LPVOID lpvParam);
INT_PTR CALLBACK DlgInfo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

#define MAX_LOADSTRING 100
#define MAXCHAR 700
#define IDC_Picture_Control 101
#define _WIN32_WINDOWS 0x0410 
#define WINVER 0x0400

								
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_YATSK_THREAD_LB, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_YATSK_THREAD_LB));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_YATSK_THREAD_LB));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_YATSK_THREAD_LB);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   g_hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
	{
		hPictureControl = CreateWindowEx(0L, TEXT("Static"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 100, 400, 200, hWnd, NULL, NULL, NULL);

		// Получение дескриптора текущего потока
		hSecThread[0] = GetCurrentThread();
		dwSecThreadID[0] = GetCurrentThreadId();
		threadPriority[0] = GetThreadPriority(hSecThread[0]);


	}return 0;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
			////////////////////////////////////////
		case IDM_NEW1:
		{
			ThrParam1 = { 1, 10, 10, hWnd };
			
			hSecThread[1] = CreateThread(NULL, 0, ThreadFunc1, &ThrParam1, 0, &dwSecThreadID[1]);			
			g_uThCount++;
			
			EnableMenuItem(GetMenu(hWnd), IDM_WAIT1, MFS_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_NEW1, MFS_GRAYED);

			// Проверка создания потока
			if (hSecThread[1] == NULL)
			{
				MessageBox(hWnd, TEXT("Поток не создан!"), NULL, MB_OK);
				break;
			}

		}break;

		case IDM_NEW2:
		{
			ThrParam2 = { 1, 10, 50, hWnd };

			hSecThread[2] = CreateThread(NULL, 0, ThreadFunc2, &ThrParam2, 0, &dwSecThreadID[2]);
			g_uThCount++;

			EnableMenuItem(GetMenu(hWnd), IDM_WAIT2, MFS_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_NEW2, MFS_GRAYED);

			// Проверка создания потока
			if (hSecThread[2] == NULL)
			{
				MessageBox(hWnd, TEXT("Поток не создан!"), NULL, MB_OK);
				break;
			}

		}break;

		case IDM_WAIT1:
		{
			ThrParam1 = { 1, 10, 10, hWnd };

			hSecThread[1] = CreateThread(NULL, 0, ThreadFunc1, &ThrParam1, CREATE_SUSPENDED, &dwSecThreadID[1]);
			g_uThCount++;

			EnableMenuItem(GetMenu(hWnd), IDM_WAIT1, MFS_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_NEW1, MFS_GRAYED);

			// Проверка создания потока
			if (hSecThread[1] == NULL)
			{
				MessageBox(hWnd, TEXT("Поток не создан!"), NULL, MB_OK);
				break;
			}

		}break;

		case IDM_WAIT2:
		{
			ThrParam1 = { 1, 10, 50, hWnd };

			hSecThread[2] = CreateThread(NULL, 0, ThreadFunc2, &ThrParam2, CREATE_SUSPENDED, &dwSecThreadID[2]);
			g_uThCount++;

			EnableMenuItem(GetMenu(hWnd), IDM_WAIT2, MFS_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_NEW2, MFS_GRAYED);

			// Проверка создания потока
			if (hSecThread[2] == NULL)
			{
				MessageBox(hWnd, TEXT("Поток не создан!"), NULL, MB_OK);
				break;
			}

		}break;

		case IDM_STOP1:
			if (hSecThread[1] != NULL)
			SuspendThread(hSecThread[1]);
			EnableMenuItem(GetMenu(hWnd), IDM_STOP1, MFS_GRAYED);
			break;

		case IDM_STOP2:
			if (hSecThread[2] != NULL)
			SuspendThread(hSecThread[2]);
			EnableMenuItem(GetMenu(hWnd), IDM_STOP2, MFS_GRAYED);
			break;

		case IDM_CONTINUE1:
			if (hSecThread[1] == NULL)
			ResumeThread(hSecThread[1]);
			EnableMenuItem(GetMenu(hWnd), IDM_STOP1, MFS_ENABLED);
			break;

		case IDM_CONTINUE2:
			if (hSecThread[2] == NULL)
			ResumeThread(hSecThread[2]);
			EnableMenuItem(GetMenu(hWnd), IDM_STOP2, MFS_ENABLED);
			break;

		case IDM_DESTROY1:
			TerminateThread(hSecThread[1], dwExitCode[1]);
			g_uThCount--;
			EnableMenuItem(GetMenu(hWnd), IDM_WAIT1, MFS_ENABLED);
			EnableMenuItem(GetMenu(hWnd), IDM_NEW1, MFS_ENABLED);
			break;

		case IDM_DESTROY2:
			TerminateThread(hSecThread[2], dwExitCode[2]);
			g_uThCount--;
			EnableMenuItem(GetMenu(hWnd), IDM_WAIT2, MFS_ENABLED);
			EnableMenuItem(GetMenu(hWnd), IDM_NEW2, MFS_ENABLED);
			break;

		case IDM_MORE1:
			nPriotity[1]++;
			SetThreadPriority(hSecThread[1], nPriotity[1]);
			break;

		case IDM_MORE2:
			nPriotity[2]++;
			SetThreadPriority(hSecThread[2], nPriotity[2]);
			break;

		case IDM_LESS1:
			nPriotity[1]--;
			SetThreadPriority(hSecThread[1], nPriotity[1]);
			break;

		case IDM_LESS2:
			nPriotity[2]--;
			SetThreadPriority(hSecThread[2], nPriotity[2]);
			break;


		///////////////////////////////////////////


		case IDM_NEW3:
		{
			hSecThread[3] = CreateThread(NULL, 0, ThreadFunc3, NULL, NULL, &dwSecThreadID[3]);
			EnableMenuItem(GetMenu(hWnd), IDM_NEW3, MFS_GRAYED);
		}
		break;

		case IDM_DESTROY3:
			TerminateThread(hSecThread[3], dwExitCode[3]);
			EnableMenuItem(GetMenu(hWnd), IDM_NEW3, MFS_ENABLED);
			break;
			
			/////////////////////////////////////////////

			// Информация о потоках
		case IDM_INFO_CUR :
			DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfo, 0);
			break;
		case IDM_INFO_THREAD1:
			DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfo, 1);
			break;
		case IDM_INFO_THREAD2:
			DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfo, 2);
			break;

		case IDM_INFO_THREAD3:
			DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfo, 3);
			break;



			/////////////////////////////////////////

		case IDM_VKL:
		{
			EnableMenuItem(GetMenu(hWnd), IDM_VKL, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(GetMenu(hWnd), IDM_VYKL, MF_BYCOMMAND | MF_GRAYED);

			hDrawMutex = CreateMutex(NULL, FALSE, NULL);
			bUseMutex = TRUE;
			EnableMenuItem(GetMenu(hWnd), IDM_VKL, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_VYKL, MF_BYCOMMAND | MF_ENABLED);
			//DWORD	dwError;
			//UINT	uRet;
			//int		iCount;

			//// create the four threads, initially suspended
			//for (iCount = 0; iCount < 4; iCount++)
			//{
			//	iRectCount[iCount] = 0;
			//	dwThreadData[iCount] = iCount;
			//	hThread[iCount] = CreateThread(NULL, 0,
			//		(LPTHREAD_START_ROUTINE)StartThread,
			//		(LPVOID)(&(dwThreadData[iCount])),
			//		CREATE_SUSPENDED,
			//		(LPDWORD)(&(dwThreadID[iCount])));
			//	if (!hThread[iCount])			// was the thread created?
			//	{
			//		dwError = GetLastError();	// for debug purposes
			//		return(FALSE);
			//	}
			//}
			//// Create a timer with a one-second period.
			//// The timer is used to update the list box.
			//uRet = SetTimer(hWnd, TIMER, 1000, NULL);
			//if (!uRet)
			//{                               // unable to create the timer
			//	dwError = GetLastError();	// for debug purposes
			//	return(FALSE);
			//}
			//// create a mutex synchronization object
			//hDrawMutex = CreateMutex(NULL, FALSE, NULL);
			//if (!hDrawMutex)
			//{                               // unable to create mutex
			//	dwError = GetLastError();	// for debug purposes
			//	KillTimer(hWnd, TIMER);   // stop the timer
			//	return(FALSE);
			//}
			//// start the threads with a priority below normal 
			//for (iCount = 0; iCount<4; iCount++)
			//{
			//	SetThreadPriority(hThread[iCount], THREAD_PRIORITY_BELOW_NORMAL);
			//	iState[iCount] = ACTIVE;
			//	ResumeThread(hThread[iCount]);
			//}
			//return(TRUE);     // Now all four threads are running!
			//WaitForSingleObject(g_hMutex, INFINITE);

			//ReleaseMutex(g_hMutex);


			//с таймером
			/*const int nTimerUnitsPerSecond = 10000000;
			int cAbrasionCount = 0;
			SYSTEMTIME st;
			LARGE_INTEGER li;

			HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);

			printf("\nConsole application with WaitableTimer by Pilipovets");
			printf("\nFirst timeout after 1 minute, then every 20 seconds\n\n");
			GetLocalTime(&st);
			printf("Start time: \t\t%.2d:%.2d:%.2d\n\n", st.wHour, st.wMinute, st.wSecond);
			li.QuadPart = -(60 * nTimerUnitsPerSecond);
			if (SetWaitableTimer(hTimer, &li, 20 * 1000, NULL, NULL, FALSE))
			{
				while (TRUE)
				{
					WaitForSingleObject(hTimer, INFINITE);
					GetLocalTime(&st);
					cAbrasionCount++;
					printf("%d.Timer abrasion: \t%.2d:%.2d:%.2d\n", cAbrasionCount, st.wHour, st.wMinute, st.wSecond);
				}
			}*/
		}break;

		case IDM_VYKL:
		{
			/*EnableMenuItem(GetMenu(hWnd), IDM_VKL, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_VYKL, MF_BYCOMMAND | MF_ENABLED);*/

			bUseMutex = FALSE;
			EnableMenuItem(GetMenu(hWnd), IDM_VKL, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(GetMenu(hWnd), IDM_VYKL, MF_BYCOMMAND | MF_GRAYED);

		}break;

			///////////////////////////////////////
		case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;


		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DlgInfo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		///////////////////////////////
		TCHAR Buf[200];

		wsprintf(Buf, TEXT("%d"), dwSecThreadID[lParam]);
		SetDlgItemText(hDlg, IDC_EDIT1, Buf);

		wsprintf(Buf, TEXT("%d"), hSecThread[lParam]);
		SetDlgItemText(hDlg, IDC_EDIT2, Buf);


		///////////////////////////////////////////
		DWORD dwExitCode;
		if (!GetExitCodeThread(hSecThread[lParam], &dwExitCode))
		{
			wsprintf(Buf, TEXT("Поток не создан"));
			SetDlgItemText(hDlg, IDC_EDIT3, Buf);
		}
		else
		{
			if (dwExitCode == STILL_ACTIVE)
			{
				if (lParam != 0 && !SuspendThread(hSecThread[lParam]) || lParam == 0)
				{
					ResumeThread(hSecThread[lParam]);
					wsprintf(Buf, TEXT("Активен"));
				}
				else
				{
					ResumeThread(hSecThread[lParam]);
					wsprintf(Buf, TEXT("Поток - спящий"));
				}
				SetDlgItemText(hDlg, IDC_EDIT3, Buf);
			}
			else
			{
				wsprintf(Buf, TEXT("Поток завершен с кодом - %d"), dwExitCode);
				SetDlgItemText(hDlg, IDC_EDIT3, Buf);
			}
		
	
		
		///////////////////////////////////////////
			threadPriority[lParam] = GetThreadPriority(hSecThread[lParam]);
			wsprintf(Buf, TEXT("%d"), threadPriority[lParam]);
			SetDlgItemText(hDlg, IDC_EDIT4, Buf);


		///////////////////////////////////////////////////////////////

		FILETIME pftCreationTime;
		FILETIME pftExitTime;
		FILETIME pftKernelTime;
		FILETIME pftUserTime;
		ULARGE_INTEGER beginTime;
		ULARGE_INTEGER endTime;
		SYSTEMTIME SystemTime;

		if (GetThreadTimes(hSecThread[lParam], &pftCreationTime, &pftExitTime, &pftKernelTime, &pftUserTime))
		{

			SYSTEMTIME sysCreationTime;
			GetLocalTime(&sysCreationTime);
			SystemTimeToFileTime(&sysCreationTime, &pftExitTime);
		}
			
		beginTime.HighPart = pftCreationTime.dwHighDateTime;
		beginTime.LowPart = pftCreationTime.dwLowDateTime;
		endTime.HighPart = pftExitTime.dwHighDateTime;
		endTime.LowPart = pftExitTime.dwLowDateTime;
		endTime.QuadPart -= beginTime.QuadPart;
		pftExitTime.dwHighDateTime = endTime.HighPart;
		pftExitTime.dwLowDateTime = endTime.LowPart;
		FileTimeToSystemTime(&pftExitTime, &SystemTime);
		wsprintf(Buf, TEXT("Время работы: %d мин. %d cек."), SystemTime.wMinute, SystemTime.wSecond);
		SetDlgItemText(hDlg, IDC_EDIT5, Buf);

		}
		///////////////////////////////

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


// Функция потока 1
DWORD WINAPI ThreadFunc1(PVOID pvParam)
{
	THREAD_PARAM *ThrParam; // Локальная переменная для хранения переданного параметра
	ThrParam = (THREAD_PARAM*)pvParam;

	TCHAR CreepingLine[MAXCHAR]; // Буфер для символов бегущей строки
	TCHAR buf[MAXCHAR] = { 0 }; // Рабочий буфер для циклического сдвига строки
	int   iBeginningIndex; // Индекс начала выводимой последовательности символов
	int   StringLength = 0; // Длина строки

	RECT  rc;
	HDC   hDC;
	int cRun = 0; // Счетчик “пробегов” строки
	int N = 4; // Количество “пробегов” в серии
	// Формирование текста бегущей строки
	wsprintf(CreepingLine, TEXT("Вторичный Поток  № 1 создала Сендецкая И.В."));
	
	// Длинна строки
	StringLength = iBeginningIndex = lstrlen(CreepingLine);
	lstrcpy(buf, CreepingLine);
	// Задание прямоугольной области вывода
	GetClientRect(ThrParam->hWnd, &rc);
	rc.top = ThrParam->yPos;
	rc.left = ThrParam->xPos;
	rc.right = rc.right - ThrParam->xPos;
	// Получение контекста для вывода строки
	hDC = GetDC(ThrParam->hWnd);
	// Бесконечный цикл вывода строк сериями по N строк
	while (TRUE)
	{
		if (bUseMutex)
			WaitForSingleObject(hDrawMutex, INFINITE);

		cRun = 0;
		int counter = 0;
		while (cRun < N - 1)
		{
			for (int j = 0; j< StringLength; j++)
			{
				if (iBeginningIndex == 0)
				{
					iBeginningIndex = StringLength;
					cRun++;
				}
				TCHAR c = buf[StringLength];
				for (int i = StringLength; i>0; i--)
					buf[i] = buf[i - 1];
				buf[0] = c;
				++counter;
				DrawText(hDC, buf, counter, &rc, DT_LEFT | DT_SINGLELINE);
				iBeginningIndex--;
				Sleep(100);
			}
		}
		ReleaseMutex(hDrawMutex);
	}

	return 0;
}

DWORD WINAPI ThreadFunc2(PVOID pvParam)
{
	THREAD_PARAM *ThrParam; // Локальная переменная для хранения переданного параметра
	ThrParam = (THREAD_PARAM*)pvParam;

	TCHAR CreepingLine[MAXCHAR]; // Буфер для символов бегущей строки
	TCHAR buf[MAXCHAR] = { 0 }; // Рабочий буфер для циклического сдвига строки
	int   iBeginningIndex; // Индекс начала выводимой последовательности символов
	int   StringLength = 0; // Длина строки

	RECT  rc;
	HDC   hDC;
	int cRun = 0; // Счетчик “пробегов” строки
	int N = 4; // Количество “пробегов” в серии
	// Формирование текста бегущей строки
	wsprintf(CreepingLine, TEXT("Вторичный Поток  № 2 создала Сендецкая И.В."));

	// Длинна строки
	StringLength = iBeginningIndex = lstrlen(CreepingLine);
	lstrcpy(buf, CreepingLine);
	// Задание прямоугольной области вывода
	GetClientRect(ThrParam->hWnd, &rc);
	rc.top = ThrParam->yPos;
	rc.left = ThrParam->xPos;
	rc.right = rc.right - ThrParam->xPos;
	// Получение контекста для вывода строки
	hDC = GetDC(ThrParam->hWnd);
	// Бесконечный цикл вывода строк сериями по N строк
	while (TRUE)
	{
		if (bUseMutex)
			WaitForSingleObject(hDrawMutex, INFINITE);
		cRun = 0;
		int counter = 0;
		while (cRun < N - 1)
		{
			for (int j = 0; j< StringLength; j++)
			{
				if (iBeginningIndex == 0)
				{
					iBeginningIndex = StringLength;
					cRun++;
				}
				TCHAR c = buf[StringLength];
				for (int i = StringLength; i>0; i--)
					buf[i] = buf[i - 1];
				buf[0] = c;
				++counter;
				DrawText(hDC, buf, counter, &rc, DT_LEFT | DT_SINGLELINE);
				iBeginningIndex--;
				Sleep(100);
			}
		}
		ReleaseMutex(hDrawMutex);
	}

	return 0;
}

DWORD WINAPI ThreadFunc3(PVOID pvParam)
{
	while (TRUE)
	{
		HDC hDC;
		HDC hMemDC;
		HANDLE hBmp;
		HANDLE hOldBmp;
		BITMAP Bmp;
		hBmp = LoadImage(g_hInst, MAKEINTRESOURCE(imageID), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		HWND hWndImage = hPictureControl;
		hDC = GetDC(hWndImage);
		hMemDC = CreateCompatibleDC(hDC);
		GetObject(hBmp, sizeof(BITMAP), &Bmp);
		hOldBmp = SelectObject(hMemDC, hBmp);
		RECT Rect;
		GetClientRect(hWndImage, &Rect);
		StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hMemDC, 0, 0, Bmp.bmWidth, Bmp.bmHeight, SRCCOPY);
		SelectObject(hMemDC, hOldBmp);
		DeleteDC(hMemDC);
		DeleteObject(hBmp);
		ReleaseDC(hWndImage, hDC);
		if (imageID == 135)
		{
			imageID = 130;
		}
		else
		{
			imageID++;
		}
		Sleep(200);
	}
	return 0;
}
