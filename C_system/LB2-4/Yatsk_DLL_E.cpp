// Yatsk_DLL_E.cpp : Defines the entry point for the application.
//


#include <stdlib.h> 
  
#include <string.h>
#include <ctype.h>
#include "windows.h"

#include <tchar.h>
#include "stdafx.h"
#include "Yatsk_DLL_E.h"
#include "..\\Yatsk_DLL\\Yatsk_DLL.h"

#pragma comment(lib, "..\\Debug\\Yatsk_dll.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
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
	LoadString(hInstance, IDC_YATSK_DLL_E, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_YATSK_DLL_E));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_YATSK_DLL_E));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_YATSK_DLL_E);
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

// Указатели на переменные
typedef int(*PPerem);

// Указатели на функции
typedef BOOL(WINAPI* PFN) (HDC, POINT*);
typedef int (WINAPI* PFN121) (double, double);
typedef float (WINAPI* PFN122) (int, int, int);
typedef void (WINAPI* PFN123) (int, int*);

// Указатели на функции СР
typedef FILE* (WINAPI* PFNSr1) ();
typedef void (WINAPI* PFNSr4) (FILE*, int*, char[]);
typedef void (WINAPI* PFNSr5) (int);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HINSTANCE hLibrary;
	static PFN pfnTriangle;
	static PPerem pDLLCallsCount = NULL;
	static PPerem pFnCallsCount = NULL;
	static HPEN hPen;
	static int sx, sy;
	

	switch (message)
	{
	case WM_CREATE:
		hLibrary = LoadLibrary(TEXT("Yatsk_DLL"));
		if (hLibrary)
		{
			pDLLCallsCount = (PPerem)GetProcAddress(hLibrary, "g_nDLLCallsCount");
			pFnCallsCount = (PPerem)GetProcAddress(hLibrary, "g_nFnCallsCount");
			(*pDLLCallsCount)++;
		}
		else
		{
			MessageBox(hWnd, _T("Библиотека не найдена"), _T("LoadLibrary"), MB_OK | MB_ICONQUESTION);
			DestroyWindow(hWnd);
			return 0;
		}
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_121:
		{
			PFN121 pfn121 = (PFN121)GetProcAddress(hLibrary, (LPCSTR)MAKEINTRESOURCE(1));
			(*pFnCallsCount)++;
			TCHAR buff[100];
			swprintf_s(buff, TEXT("int Fun121(double, double)\nx = 2; y = 2\nRez = %d\ng_nFnCallsCount = %d\ng_nDLLCallsCount = %d"),
				pfn121(2, 2), *pFnCallsCount, *pDLLCallsCount);
			MessageBox(hWnd, buff, _T("LoadLibrary"), MB_OK | MB_ICONQUESTION);
			break;
		}
		case IDM_122:
		{
			PFN122 pfn122 = (PFN122)GetProcAddress(hLibrary, "Fn122");
			(*pFnCallsCount)++;
			TCHAR buff[200];
			swprintf_s(buff,
				TEXT("float Fun122(int, int, int)\nx = 2; y = 2; z = 2\nRez = %f\ng_nFnCallsCount = %d\ng_nDLLCallsCount = %d"),
				pfn122(2, 2, 2), *pFnCallsCount, *pDLLCallsCount);
			MessageBox(hWnd, buff, _T("LoadLibrary"), MB_OK | MB_ICONQUESTION);
		}
		break;
		case IDM_123:
		{
			PFN123 pfn123 = (PFN123)GetProcAddress(hLibrary, "Fn123");
			(*pFnCallsCount)++;
			TCHAR buff[200];
			int y = 2;
			pfn123(2, &y);
			swprintf_s(buff, TEXT("void Fun123(int, int *)\nx = 2; y = 2\nRez = %f\ng_nFnCallsCount = %d\ng_nDLLCallsCount = %d"),
				y, *pFnCallsCount, *pDLLCallsCount);
			MessageBox(hWnd, buff, _T("LoadLibrary"), MB_OK | MB_ICONQUESTION);
		}
		break;
		//////////////////////////////////////

		case IDM_SR:
			PFNSr1 pfnSr1 = (PFNSr1)GetProcAddress(hLibrary, "FnSR1");
			FILE* fileExists = pfnSr1();

			PFNSr4 pfnSr4 = (PFNSr4)GetProcAddress(hLibrary, "FnSR4");
			int wordCount = 0;
			char buff2[1000] = { "" };
			pfnSr4(fileExists, &wordCount, buff2);
			PFNSr5 pfnSr5 = (PFNSr5)GetProcAddress(hLibrary, "FnSR5");
			pfnSr5(wordCount);

			break;

			///////////////////////////////////
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
		SelectObject(hdc, hPen);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		FreeLibrary(hLibrary);
		DeleteObject(hPen);
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
