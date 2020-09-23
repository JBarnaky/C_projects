#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>  
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "Header.h"

HINSTANCE hInst;

// Global variables  

// The main window class name.  
static TCHAR szWindowClass[] = _T("sp_pr2_class");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("Title");

HINSTANCE g_hInst;

// Forward declarations of functions included in this code module:  
LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK _tWinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Pr2_WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ASTERISK));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 255, 0));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = g_lpszClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ASTERISK));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Ошибка регистрации класса окна!"),
			_T("Ошибка 1"),
			NULL);

		return 1;
	}

	g_hInst = hInstance;

	HWND hWnd = CreateWindow(
		wcex.lpszClassName,
		g_lpszClassName,
		WS_OVERLAPPEDWINDOW - WS_MAXIMIZEBOX | WS_VISIBLE,
		220, 170,
		520, 280,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Ошибка создания окна!"),
			_T("Ошибка 2"),
			NULL);

		return 1;
	}
 
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);
 
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	PAINTSTRUCT ps;
	HDC hdc = GetDC(hWnd);
	HBRUSH hBrush, holdBrush;
	HPEN hPen, holdPen;
	RECT rect;

	static HWND hButtonSave;
	static HWND hButtonAdd;
	static HWND hButtonExit;
	static HWND hEdit;
	static HWND hListBox;
	static HWND hButtonUnto;

	#define IDC_BTN_SAVE 100
	#define IDC_BTN_ADD 101
	#define IDC_EDIT1 102
	#define IDC_LISTBOX 103
	#define IDC_BTN_UNTO 104

	switch (message)
	{
	case WM_CREATE:
		MessageBox(NULL,
			_T("Выполняется обработка WM_CREATE"),
			_T("WM_CREATE"),
			NULL);

		{
			if (!(hEdit = CreateWindowEx(0L, "Edit", "Редактор",
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				20, 50, 160, 40, hWnd, (HMENU)(IDC_EDIT1),
				g_hInst, NULL))) return (-1);
			if (!(hListBox = CreateWindowEx(0L, "ListBox", "Список",
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				200, 50, 160, 180, hWnd, (HMENU)(IDC_LISTBOX),
				g_hInst, NULL))) return (-1);
			if (!(hButtonSave = CreateWindowEx(0L, "Button", "В буфер",
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				20, 240, 80, 24, hWnd, (HMENU)(IDC_BTN_SAVE),
				g_hInst, NULL))) return (-1);
			if (!(hButtonAdd = CreateWindowEx(0L, "Button", "В список",
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				120, 240, 80, 24, hWnd, (HMENU)(IDC_BTN_ADD),
				g_hInst, NULL))) return (-1);
			if (!(hButtonExit = CreateWindowEx(0L, "Button", "Выход",
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				220, 240, 80, 24, hWnd, (HMENU)(IDCANCEL),
				g_hInst, NULL))) return (-1);
			if (!(hButtonUnto = CreateWindowEx(0L, "Button", "Unto",
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				0, 0, 80, 24, hWnd, (HMENU)(IDC_BTN_UNTO),
				g_hInst, NULL))) return (-1);
		}return 0;
	case WM_COMMAND:
	{
		TCHAR lpszBuff[200];
		TCHAR lpszHex[200];

		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		static TCHAR pszTextBuff[500];
		switch (wmId)
		{
		case IDC_BTN_UNTO:
			TextOut(hdc, 100, 10, lpszBuff,
				wsprintf(lpszBuff, TEXT(szWindowClass)));

			TextOut(hdc, 100, 30, lpszHex,
				wsprintf(lpszHex, TEXT("%02x"), TEXT(szTitle)));

			DestroyWindow(hButtonUnto);

			if (!(hButtonUnto = CreateWindowEx(0L, "Button", "Выход",
				WS_CHILD | WS_BORDER | WS_VISIBLE,
				0, 0, 80, 24, hWnd, (HMENU)(IDCANCEL),
				g_hInst, NULL))) return (-1);

			break;
		case IDCANCEL:
			DestroyWindow(hWnd);
			break;
		case IDC_BTN_SAVE:
		{
			int cch;
			cch = SendMessage(hEdit, WM_GETTEXT, 500, (LPARAM)pszTextBuff);
			if (cch == 0)
				MessageBox(hWnd, "Введите текст", "Читаем Edit", MB_OK);
			else {
				TCHAR Buff1[500] = { 0 };
				SYSTEMTIME st; GetSystemTime(&st);
				wsprintf(Buff1, "Время : %d ч %d мин %d сек\n",
					st.wHour, st.wMinute, st.wSecond);
				lstrcat(Buff1, __TEXT("Текст в памяти: "));
				lstrcat(Buff1, pszTextBuff);
				MessageBox(hWnd, Buff1, "Содержимое буфера", MB_OK);
			}
		}
		break;
		case IDC_BTN_ADD:
		{
			int ind;
			ind = SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)pszTextBuff);
			if (ind == LB_ERR)
				MessageBox(hWnd, "Ошибка в списке", "", MB_OK);
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

		break;
	case WM_LBUTTONDOWN:

		BOOL TxtOut(HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString);
		{
			HDC hdc = GetDC(hWnd);

			TCHAR lpszBuff[200] = TEXT("Обработка сообщения WM_LBUTTONDOWN, которое посылается в окно при щелчке левой кнопки мыши");

			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			/*TextOut(hdc, x, y, lpszBuff,
				wsprintf(lpszBuff, TEXT("OutString %s, StartPosition: X=%d, Y=%d"), TEXT("Обработка сообщения WM_LBUTTONDOWN, которое посылается в окно при щелчке левой кнопки мыши"), x, y));*/

			GetClientRect(hWnd, &rect);
			SetTextColor(hdc, 0x00000000);
			SetBkMode(hdc, TRANSPARENT);

			rect.left = x;
			rect.top = y;

			DrawText(hdc, lpszBuff, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
		}
	case WM_PAINT:

		TCHAR lpszBuff[200];

		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 20, 100, lpszBuff,
			wsprintf(lpszBuff, TEXT("Вывод текста при обработке сообщения WM_PAINT. Это соообщение окно получает после того, как оно было закрыто другим окном и затем открыто.")));

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		int msgboxID2 = MessageBox(
			NULL,
			(LPCSTR)g_lpszDestroyMessage,
			(LPCSTR)"WM_DESTROY",
			MB_OK);

		switch (msgboxID2)
		{
		case IDOK:
			PostQuitMessage(12);
			break;
			return 0;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}