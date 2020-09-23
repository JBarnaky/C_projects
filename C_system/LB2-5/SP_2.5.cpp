// SP_2.5.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SP_2.5.h"
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LPCTSTR g_lpszClassName = TEXT("SP_LB2.5");
LPCTSTR g_lpszAplicationTitle = TEXT("Лабароторная работа Яцкевича К.В. гр.60322-1");

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

HANDLE hFile = NULL;
HANDLE ProcHandle;
static HMENU hMenu;

void WndProc_OnPaint(HWND);
void WndProc_OnCommand(HWND, int, HWND, UINT);
void WndProc_OnClose(HWND);
void WndProc_OnDestroy(HWND);

int compare(const int*, const int*);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SP_25));
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Ошибка регистрации класса окна"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_SP_25));
	hWnd = CreateWindowEx(NULL, g_lpszClassName, g_lpszAplicationTitle, WS_OVERLAPPEDWINDOW,
		600, 200, 500, 300, NULL, hMenu, hInstance, NULL);
	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SP_25));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SP_25);
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

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
	   MessageBox(NULL, TEXT("Окно не создано"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{

		HANDLE_MSG(hWnd, WM_COMMAND, WndProc_OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, WndProc_OnPaint);
		HANDLE_MSG(hWnd, WM_CLOSE, WndProc_OnClose);
		HANDLE_MSG(hWnd, WM_DESTROY, WndProc_OnDestroy);
	default: return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return FALSE;
}

void WndProc_OnPaint(HWND hWnd)
{
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);
	}

void WndProc_OnCommand(HWND hWnd, int wmld, HWND, UINT)
{
	LPTSTR fileName;
	static HANDLE hFile;
	static HANDLE hFileMap;
	static LPVOID lpvFile;
	LPSTR  lpchANSI;
	static DWORD  dwFileSize;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;

	FILE* add_file = NULL;
	int wordCount = 0;
	char ch;
	char glasn[] = "уеыаоэяиюУЕЫАОЭЯИЮ";
	
	//char buff[32] = { 0 };

	char addStr[80] = "";
	FILE* fileExist;
	fopen_s(&fileExist, "temp.txt", "a+");

	
	switch (wmld)
	{
	case IDM_CREATE_FILE:
	{
		fileName = TEXT("test.txt");
		if (!CopyFile(fileName, TEXT("1.txt"), FALSE))
		{
			MessageBox(NULL, TEXT("Ошибка создания файла"), TEXT("Ошибка"), MB_OK);
			break;
		}
		hFile = CreateFile(TEXT("1.txt"), GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//создание или открытие объекта ядра  "файл". GENERIC_WRITE- Запись в файл разрешена
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, L"Ошибка открытия файла.", L"Ошибка", MB_OK);
			break;
		}
		EnableMenuItem(hMenu, IDM_CREATE_FILE, MF_GRAYED);
		EnableMenuItem(hMenu, IDM_CREAT_PFILE, MF_ENABLED);

		break;

	case IDM_CREAT_PFILE:
	{
		dwFileSize = GetFileSize(hFile, NULL);
		hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwFileSize + 64 * sizeof(WCHAR), NULL);//Создание объекта ядра "проецируемый файл".
		//При успешном выполнении создается объект "проецируемый файл" (file-mapping object) который содержит информацию,
		//необходимую операционной системе при управлении спроецированным в память файлом. 
		if (hFileMap == NULL)
		{
			MessageBox(NULL, TEXT("Ошибка открытия проецируемого файла."), TEXT("Ошибка"), MB_OK);
		}
		else
		{
			EnableMenuItem(hMenu, IDM_SPASE, MF_ENABLED);
			EnableMenuItem(hMenu, IDM_CREAT_PFILE, MF_GRAYED);
		}
		break;
	}
	case IDM_SPASE:
	{
		lpvFile = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);// Проецирование файловых данных на адресное пространство процесса
		//оздав объект "проецируемый файл", нужно, чтобы система, зарезервировав регион адресного пространства под данные файла, 
		//   передала их как физическую память, спроецированную на регион. 
		if (lpvFile == NULL)
		{
			MessageBox(NULL, TEXT("Ошибка при проецировании файла."), TEXT("Ошибка"), MB_OK);
			CloseHandle(hFileMap);
			CloseHandle(hFile);
			break;
		}


		lpchANSI = (LPSTR)lpvFile;
		lpchANSI[dwFileSize] = 0;

		// 4. Получение колиества слов с гласной

		for (int i = 0; i <= strlen(lpchANSI); i++)
		{
			
			
			//ch = lpchANSI[i];
			for (int l = 0; l <= strlen(glasn); l++)
			{
				if ( i > 0 && lpchANSI[i] == glasn[l] && lpchANSI[i - 1] == ' ')
				{
					wordCount ++;
				}
				if (lpchANSI[i] == glasn[l] && i == 0)
				{
					wordCount ++;
				}
				
			}
		}
		sprintf_s(addStr, "\nКоличество слов начинающихся с гласных = %d", wordCount, 80);
		lstrcpy((LPWSTR)&lpchANSI[dwFileSize], (LPWSTR)addStr);
		dwFileSize += lstrlen((LPTSTR)addStr);
		
		
		EnableMenuItem(hMenu, IDM_SPASE, MF_GRAYED);
		EnableMenuItem(hMenu, IDM_CLOSE, MF_ENABLED);
	}
	break;
	case IDM_CLOSE:
	{
		UnmapViewOfFile(lpvFile);
		EnableMenuItem(hMenu, IDM_CLOSED, MF_ENABLED);
		EnableMenuItem(hMenu, IDM_CLOSE, MF_GRAYED);

	} break;
	case IDM_CLOSED:
	{
		CloseHandle(hFileMap);
		EnableMenuItem(hMenu, IDM_CLOSED, MF_GRAYED);
		EnableMenuItem(hMenu, IDM_CLOSEF, MF_ENABLED);
	}
	break;
	case IDM_CLOSEF:
	{
		SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
		SetEndOfFile(hFile);
		CloseHandle(hFile);
		EnableMenuItem(hMenu, IDM_RESULT, MF_ENABLED);
		EnableMenuItem(hMenu, IDM_CLOSEF, MF_GRAYED);

	}
	break;
	case IDM_RESULT:
	{
		si.cb = sizeof(si);
		si.wShowWindow = SW_SHOW;
		si.dwFlags = STARTF_USESHOWWINDOW;
		wchar_t buf[1000];
		wsprintf(buf, TEXT("C:\\Windows\\notepad.exe 1.txt"));
		if (CreateProcess(TEXT("C:\\Windows\\notepad.exe"), buf, NULL, NULL, 0, 0, NULL, NULL, &si, &pi))
		{
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			EnableMenuItem(hMenu, IDM_CREATE_FILE, MF_ENABLED);
		}
	}
	break;
	}
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	default:

		break;
		 
	}

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
void WndProc_OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
	FORWARD_WM_DESTROY(hWnd, DefWindowProc);
}



void WndProc_OnClose(HWND hWnd)
{
	DestroyWindow(hWnd);
	FORWARD_WM_CLOSE(hWnd, DefWindowProc);
}