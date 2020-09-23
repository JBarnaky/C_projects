#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"
#include "sp_pr3_4_1.h"



LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

LPCTSTR g_lpszClassName = TEXT("sp_pr2_class"); //��� ������
LPCTSTR g_lpszAplicationTitle = TEXT("������� ���� ����������. ����������� <���������, �����>");
HINSTANCE g_hInstance;

BOOL WndProc_OnCreate(HWND, LPCREATESTRUCT);
void WndProc_OnCommand(HWND, int, HWND, UINT);
void WndProc_OnMenuSelect(HWND, HMENU, int, HMENU, UINT);
void WndProc_OnRButtonDown(HWND, BOOL, int, int, UINT);
void WndProc_OnPaint(HWND);
void WndProc_OnDestroy(HWND);


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)

{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;
	g_hInstance=hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = Pr2_WndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("������ ����������� ������ ����!"), TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	hWnd = CreateWindowEx(NULL, g_lpszClassName, g_lpszAplicationTitle, (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX), //WS_OVERLAPPEDWINDOW ��� ����� MAXIMIZEBOX
		0, 0, 700, 700, NULL, hMenu, hInstance, NULL);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("���� �� �������!"), TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd,hAccel,&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	DestroyAcceleratorTable(hAccel);
	return msg.wParam;
}

BOOL CreateMenuItem(HMENU hMenu, HMENU hFloatMenu, UINT wmld, LPWSTR itemName)
{
	MENUITEMINFO menuItem;
	menuItem.cbSize = sizeof(MENUITEMINFO);
	GetMenuItemInfo(hMenu, IDM_EDIT_SELECT, FALSE, &menuItem);
	GetMenuItemInfo(hMenu, IDM_EDIT_COPY, FALSE, &menuItem);
	menuItem.fState = MFS_ENABLED;
	menuItem.fMask = MIIM_STATE | MIIM_TYPE | MIIM_ID;
	menuItem.dwTypeData = itemName;
	menuItem.fType = MFT_STRING;
	menuItem.cch = sizeof(itemName);
	menuItem.wID = wmld;
	return InsertMenuItem(hFloatMenu, wmld, FALSE, &menuItem);
}

// ������� ���������

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

{

	//int wmld = LOWORD(wParam), wmEvent = HIWORD(wParam);

	switch (msg)
	{
		HANDLE_MSG(hWnd, WM_CREATE, WndProc_OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, WndProc_OnCommand);
		HANDLE_MSG(hWnd, WM_MENUSELECT, WndProc_OnMenuSelect);
		HANDLE_MSG(hWnd, WM_RBUTTONDOWN, WndProc_OnRButtonDown);
		HANDLE_MSG(hWnd, WM_PAINT, WndProc_OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, WndProc_OnDestroy);
	default: // ����� "����������� �� ���������"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;// ��� ������ � "break"

}
		
		BOOL WndProc_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
		{
			HMENU hMenu = GetMenu(hWnd);
			HMENU hSubMenu = GetSubMenu(hMenu, 0);
			AppendMenu(hSubMenu, NULL, IDM_FILE_CLOSE, TEXT("������� ��������"));
			return TRUE;
		}
	
		void WndProc_OnCommand(HWND hWnd, int wmld, HWND hWnd1, UINT wmEvent)
	{
		//wmld = LOWORD(wParam);
		static TCHAR Buf1[500];

		switch (wmld)
		{

		case IDM_FILE_EXIT:
			DestroyWindow(hWnd);
			break;

		case IDM_FILE_NEW:
		{
			MessageBox(hWnd, TEXT("������ ����� '�������'"), TEXT("���� File"), MB_OK);
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_SELECT, MFS_ENABLED);
		} break;

		case IDM_FILE_OPEN:
		{
			MessageBox(hWnd, TEXT("������ ����� '�������'"), TEXT("���� File"), MB_OK);
		} break;

		case IDM_EDIT_SELECT:
		{
			MessageBox(hWnd, TEXT("������ ����� '��������'"), TEXT("���� Edit"), MB_OK);
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_COPY, MFS_ENABLED);
		} break;

		case IDM_EDIT_CUT:
		{
			MessageBox(hWnd, TEXT("������ ����� '��������'"), TEXT("���� Edit"), MB_OK);
		} break;

		case IDM_EDIT_COPY:
		{
			MessageBox(hWnd, TEXT("������ ����� '����������'"), TEXT("���� Edit"), MB_OK);
		} break;

		case IDM_EDIT_PASTE:
		{
			MessageBox(hWnd, TEXT("������ ����� '��������'"), TEXT("���� Edit"), MB_OK);
		} break;

		case IDM_HELP_HELP:
		{
			MessageBox(hWnd, TEXT("������ ����� '������'"), TEXT("���� Help"), MB_OK);
		} break;

		case IDM_FILE_CLOSE:
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_COPY, MFS_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_SELECT, MFS_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_CUT, MFS_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_PASTE, MFS_GRAYED);
			break;

		/*case IDM_HELP_ABOUT:
		{
			MessageBox(hWnd, TEXT("������ ����� '� ���������'"), TEXT("���� Help"), MB_OK);
		} break;*/

		default:
			static TCHAR Buf1[500];
			wsprintf(Buf1, TEXT("������� � ��������������� %d �� �����������"), wmld);
			MessageBox(hWnd, Buf1, TEXT("����"), MB_OK);
			
			break;
		}
	} 

		void WndProc_OnMenuSelect(HWND hWnd, HMENU hmenu, int wmld, HMENU hmenuPopup, UINT flags)
	{
		HDC hdc1;
		LPCTSTR lpszMsgSpace = TEXT("_______________________");
		TCHAR buf[300];
		HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
		int size = LoadString(hInst, wmld, buf, 300);
		hdc1 = GetDC(hWnd);
		RECT rt;
		GetClientRect(hWnd, &rt);
		TextOut(hdc1, rt.left + 10, rt.bottom - 25, lpszMsgSpace, lstrlen(lpszMsgSpace));
		TextOut(hdc1, rt.left + 10, rt.bottom - 30, buf, lstrlen(buf));
		ReleaseDC(hWnd,hdc1);
	}

		void WndProc_OnRButtonDown(HWND hWnd, BOOL fDoubleClick, int xPos, int yPos, UINT flags)
	{
		HMENU hMenu = GetMenu(hWnd);
		HMENU hFloatMenu = CreatePopupMenu();

		CreateMenuItem(hMenu, hFloatMenu, IDM_EDIT_SELECT, TEXT("��������"));
		CreateMenuItem(hMenu, hFloatMenu, IDM_EDIT_COPY, TEXT("����������"));
		TrackPopupMenu(hFloatMenu, TPM_CENTERALIGN | TPM_LEFTBUTTON |
			TPM_VCENTERALIGN, xPos, yPos, 0, hWnd, NULL);
		DestroyMenu(hFloatMenu);

	}

		void WndProc_OnPaint(HWND hWnd)
		{// ����� ��� ���������� ���� (�����������)
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);  // ��������� ��������� ���
			EndPaint(hWnd, &ps); // ���������� ���������� ����
		}
		void WndProc_OnDestroy(HWND hWnd)
		{  // ���������� ������ ����������
			PostQuitMessage(0); // ������� WM_QUIT ����������

		}