// SP_PR_5_SR.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SP_PR_5_SR.h"

#define MAX_LOADSTRING 100
static HWND hEdit;
static HWND hListBox;
#define IDC_EDIT2 109
#define IDC_LISTBOX2 110
HWND hWnd;
UINT imageID=130;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ProcDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK bmpProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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
	LoadString(hInstance, IDC_SP_PR_5_SR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SP_PR_5_SR));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SP_PR_5_SR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SP_PR_5_SR);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_FILE_DIALOG1:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ProcDialog);
			break;

		case IDM_FILE_DIALOG2:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, bmpProc);
			break;

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

INT_PTR CALLBACK ProcDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		///////////////////////

		if (!(hEdit = CreateWindowEx(0L, TEXT("Edit"), TEXT("��������"), WS_CHILD | WS_BORDER | WS_VISIBLE, 20, 20, 160, 40, hDlg, (HMENU)(IDC_EDIT2), NULL, NULL)))
			return (-1);

		if (!(hListBox = CreateWindowEx(0L, TEXT("ListBox"), TEXT("������"), WS_CHILD | WS_BORDER | WS_VISIBLE, 200, 20, 160, 180, hDlg, (HMENU)(IDC_LISTBOX2), NULL, NULL)))
			return (-1);


		/////////////////////

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		////////////////////////////////////
		static TCHAR pszTextBuff[500];

		switch LOWORD(wParam)
		{

		case IDC_BUTTON_BUF:
		{
			int cch = SendMessage(hEdit, WM_GETTEXT, 500, (LPARAM)pszTextBuff);

			if (cch == 0)
				MessageBox(hWnd, TEXT("������� �����"), TEXT("������ Edit"), MB_OK);
			else
			{
				TCHAR Buff1[500] = { 0 };

				SYSTEMTIME st;
				GetSystemTime(&st);
				wsprintf(Buff1, TEXT("�����: %d � %d ��� %d ���\n"), st.wHour, st.wMinute, st.wSecond);
				lstrcat(Buff1, TEXT("����� � ������: "));
				lstrcat(Buff1, pszTextBuff);
				MessageBox(hWnd, Buff1, TEXT("���������� ������"), MB_OK);

			}
		} break;

		case IDC_BUTTON_LIST:
		{
			int ind = SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)pszTextBuff);
			if (ind == LB_ERR)
				MessageBox(hWnd, TEXT("������ � ������"), TEXT(""), MB_OK);

		} break;
		//////////////////////////////////////////
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK bmpProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)

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
		WORD wmld = LOWORD(wParam);
		switch (wmld)
		{
		case IDC_BUTTON_NEXT:
		{
			HDC hDC;
			HDC hMemDC;
			HANDLE hBmp;
			HANDLE hOldBmp;
			BITMAP Bmp;
			hBmp = LoadImage(hInst, MAKEINTRESOURCE(imageID), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
			HWND hWndImage = GetDlgItem(hDlg, IDC_PICTURE1);
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

			if (imageID > 134)
			{
				imageID = 130;
			}
			else
			{
				imageID++;
			}
		}
		break;
		}
	}
	return (INT_PTR)FALSE;
}
