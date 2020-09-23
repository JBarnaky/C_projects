#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"
#include "sp_pr3.h"


LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

LPCTSTR g_lpszClassName = TEXT("sp_pr2_class"); //имя класса
LPCTSTR g_lpszAplicationTitle = TEXT("Главное окно приложения. Программист <Яцкевич, Павел>");
HINSTANCE hInstance;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)

{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;

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
		MessageBox(NULL, TEXT("Ошибка регистрации класса окна!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	hWnd = CreateWindowEx(NULL, g_lpszClassName, g_lpszAplicationTitle, (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX), //WS_OVERLAPPEDWINDOW без флага MAXIMIZEBOX
		0, 0, 700, 700, NULL, hMenu, hInstance, NULL);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
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

// Оконная процедура

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

{

	int wmld, wmEvent;
	HDC hdc;

	switch (msg)
	{
	case WM_CREATE:
	{
		HMENU hMenu = GetMenu(hWnd);
		HMENU hSubMenu = GetSubMenu(hMenu, 0);
		AppendMenu(hSubMenu, NULL, IDM_FILE_CLOSE, TEXT("Закрыть документ"));
		return 0;
		break;
	}
	return 0;

	case WM_COMMAND:
	{
		wmld = LOWORD(wParam);
		static TCHAR Buf1[500];

		switch (wmld)
		{

		case IDM_FILE_EXIT:
			DestroyWindow(hWnd);
			break;

		case IDM_FILE_NEW:
		{
			MessageBox(hWnd, TEXT("Выбран пункт 'Создать'"), TEXT("Меню File"), MB_OK);
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_SELECT, MFS_ENABLED);
		} break;

		case IDM_FILE_OPEN:
		{
			MessageBox(hWnd, TEXT("Выбран пункт 'Открыть'"), TEXT("Меню File"), MB_OK);
		} break;

		case IDM_EDIT_SELECT:
		{
			MessageBox(hWnd, TEXT("Выбран пункт 'Выделить'"), TEXT("Меню Edit"), MB_OK);
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_COPY, MFS_ENABLED);
		} break;

		case IDM_EDIT_CUT:
		{
			MessageBox(hWnd, TEXT("Выбран пункт 'Вырезать'"), TEXT("Меню Edit"), MB_OK);
		} break;

		case IDM_EDIT_COPY:
		{
			MessageBox(hWnd, TEXT("Выбран пункт 'Копировать'"), TEXT("Меню Edit"), MB_OK);
		} break;

		case IDM_EDIT_PASTE:
		{
			MessageBox(hWnd, TEXT("Выбран пункт 'Вставить'"), TEXT("Меню Edit"), MB_OK);
		} break;

		case IDM_HELP_HELP:
		{
			MessageBox(hWnd, TEXT("Выбран пункт 'Помощь'"), TEXT("Меню Help"), MB_OK);
		} break;

		case IDM_FILE_CLOSE:
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_COPY, MFS_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_SELECT, MFS_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_CUT, MFS_GRAYED);
			EnableMenuItem(GetMenu(hWnd), IDM_EDIT_PASTE, MFS_GRAYED);
			break;

		/*case IDM_HELP_ABOUT:
		{
			MessageBox(hWnd, TEXT("Выбран пункт 'О программе'"), TEXT("Меню Help"), MB_OK);
		} break;*/

		default:
			wsprintf(Buf1, TEXT("Команда с идентификатором %d не реализована"), wmld);
			MessageBox(hWnd, Buf1, TEXT("Меню"), MB_OK);
			return(DefWindowProc(hWnd, msg, wParam, lParam));
		}
	} break;

	case WM_MENUSELECT:
	{
		HDC hdc1;
		LPCTSTR lpszMsgSpace = TEXT("_______________________");
		TCHAR buf[300];
		HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
		int size = LoadString(hInst, LOWORD(wParam), buf, 300);
		hdc1 = GetDC(hWnd);
		RECT rt;
		GetClientRect(hWnd, &rt);
		TextOut(hdc1, rt.left + 10, rt.bottom - 25, lpszMsgSpace, lstrlen(lpszMsgSpace));
		TextOut(hdc1, rt.left + 10, rt.bottom - 30, buf, lstrlen(buf));
		ReleaseDC(hWnd,hdc1);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		HMENU hMenu = GetMenu(hWnd);
		DWORD xyPos = GetMessagePos();
		WORD xPos = LOWORD(xyPos), yPos = HIWORD(xyPos);

		HMENU hFloatMenu = CreatePopupMenu();
		int i = 0;
		CreateMenuItem(hMenu, hFloatMenu, IDM_EDIT_SELECT, TEXT("Выделить"));
		CreateMenuItem(hMenu, hFloatMenu, IDM_EDIT_COPY, TEXT("Копировать"));
		TrackPopupMenu(hFloatMenu, TPM_CENTERALIGN | TPM_LEFTBUTTON |
			TPM_VCENTERALIGN, xPos, yPos, 0, hWnd, NULL);
		DestroyMenu(hFloatMenu);
		return 0;

	}

	case WM_PAINT:    // Вывод при обновлении окна (перерисовка)
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);  // Получение контекста для
		EndPaint(hWnd, &ps); // Завершение обновления окна
		break;

	case WM_DESTROY:  // Завершение работы приложения
		PostQuitMessage(0); // Посылка WM_QUIT приложению
		break;
	default: // Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;// Для ветвей с "break"

}