#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"
#include <wingdi.h>

#define MAX_BYTES  10000

LRESULT CALLBACK Pr5_WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK OpenFile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK bmpProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

LPCTSTR g_lpszClassName = TEXT("sp_pr5_class"); //имя класса
LPCTSTR g_lpszAplicationTitle = TEXT("Главное окно приложения. Программист <Сендецкая, Ирина>");
HINSTANCE g_hInstance;

BOOL WndProc_OnCreate(HWND, LPCREATESTRUCT);
void WndProc_OnCommand(HWND, int, HWND, UINT);
//void WndProc_OnMenuSelect(HWND, HMENU, int, HMENU, UINT);
//void WndProc_OnRButtonDown(HWND, BOOL, int, int, UINT);
void WndProc_OnPaint(HWND);
void WndProc_OnDestroy(HWND);
BOOL DlgProc_OnInitDialog(HWND hDlg, HWND fokus, LPARAM lParam);
void DlgProc_OnCommand1(HWND hWnd, int wmld, HWND hWnd1, UINT wmEvent);

HWND g_hDlgModeless = NULL;

TCHAR FileName[250];
LPTSTR FileName1 = TEXT("1.bmp");
DWORD dwNumbOfBytes = MAX_BYTES;

TCHAR Buffer[MAX_BYTES];
HANDLE hf = NULL;
OPENFILENAME ofn;
HWND hWnd;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)

{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;
	g_hInstance=hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = Pr5_WndProc;
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
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (g_hDlgModeless == 0 || !IsDialogMessage(g_hDlgModeless, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	DestroyAcceleratorTable(hAccel);
	return msg.wParam;
}

BOOL CreateMenuItem(HMENU hMenu, HMENU hFloatMenu, UINT wmld, LPSTR itemName)
{
	MENUITEMINFO menuItem;
	menuItem.cbSize = sizeof(MENUITEMINFO);
	//GetMenuItemInfo(hMenu, IDM_EDIT_SELECT, FALSE, &menuItem);
	menuItem.fState = MFS_ENABLED;
	menuItem.fMask = MIIM_STATE | MIIM_TYPE | MIIM_ID;
	menuItem.dwTypeData = itemName;
	menuItem.fType = MFT_STRING;
	menuItem.cch = sizeof(itemName);
	menuItem.wID = wmld;
	return InsertMenuItem(hFloatMenu, wmld, FALSE, &menuItem);
}

// Оконная процедура

LRESULT CALLBACK Pr5_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

{

	switch (msg)
	{
		HANDLE_MSG(hWnd, WM_CREATE, WndProc_OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, WndProc_OnCommand);
		//HANDLE_MSG(hWnd, WM_MENUSELECT, WndProc_OnMenuSelect);
		//HANDLE_MSG(hWnd, WM_RBUTTONDOWN, WndProc_OnRButtonDown);
		HANDLE_MSG(hWnd, WM_PAINT, WndProc_OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, WndProc_OnDestroy);
	default: // Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;// Для ветвей с "break"

}
		
		BOOL WndProc_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
		{
			HMENU hMenu = GetMenu(hWnd);
			HMENU hSubMenu = GetSubMenu(hMenu, 0);
			return TRUE;
		}
	
		void WndProc_OnCommand(HWND hWnd, int wmld, HWND hWnd1, UINT wmEvent)
	{
		HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
		//wmld = LOWORD(wParam);
		static TCHAR Buf1[500];

		switch (wmld)
		{

		case IDM_FILE_EXIT:
			DestroyWindow(hWnd);
			break;

		case IDM_FILE_OPEN:
		{
			MessageBox(hWnd, TEXT("Выбран пункт 'Открыть'"), TEXT("Меню FILE"), MB_OK);

		} break;

		case IDM_VIEW_TEXT:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, OpenFile);
		} break;

		case IDM_VIEW_BMP:
		{
			CreateDialog(hInst, MAKEINTRESOURCE(IDR_DIALOG3), hWnd, bmpProc);
		} break;

		
		case IDM_HELP_HELP:
		{
			MessageBox(hWnd, TEXT("Выбран пункт 'Помощь'"), TEXT("Меню Help"), MB_OK);
		} break;

	
		case IDM_HELP_ABOUT:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
		} break;

		default:
			static TCHAR Buf1[500];
			wsprintf(Buf1, TEXT("Команда с идентификатором %d не реализована"), wmld);
			MessageBox(hWnd, Buf1, TEXT("Меню"), MB_OK);
			
			break;
		}
	} 

	/*	void WndProc_OnMenuSelect(HWND hWnd, HMENU hmenu, int wmld, HMENU hmenuPopup, UINT flags)
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
	}*/

	/*	void WndProc_OnRButtonDown(HWND hWnd, BOOL fDoubleClick, int xPos, int yPos, UINT flags)
	{
		HMENU hMenu = GetMenu(hWnd);
		HMENU hFloatMenu = CreatePopupMenu();

		CreateMenuItem(hMenu, hFloatMenu, IDM_EDIT_SELECT, TEXT("Выделить"));
		CreateMenuItem(hMenu, hFloatMenu, IDM_EDIT_COPY, TEXT("Копировать"));
		TrackPopupMenu(hFloatMenu, TPM_CENTERALIGN | TPM_LEFTBUTTON |
			TPM_VCENTERALIGN, xPos, yPos, 0, hWnd, NULL);
		DestroyMenu(hFloatMenu);

	}*/

		void WndProc_OnPaint(HWND hWnd)
		{// Вывод при обновлении окна (перерисовка)
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);  // Получение контекста для
			EndPaint(hWnd, &ps); // Завершение обновления окна
		}
		void WndProc_OnDestroy(HWND hWnd)
		{  // Завершение работы приложения
			PostQuitMessage(0); // Посылка WM_QUIT приложению

		}

		INT_PTR CALLBACK OpenFile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
		{
			UNREFERENCED_PARAMETER(lParam);
			TCHAR buf[500] = TEXT("");

			switch (message)
			{
			
			case WM_INITDIALOG:
			{
				LPCTSTR lpszText1 = TEXT("Шаг 1: Начало работы\n");
				lstrcat(buf, lpszText1);

				SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), buf);

				CheckDlgButton(hDlg, IDC_BUTTON1, BS_DEFPUSHBUTTON);
				
				return (INT_PTR)TRUE;
			}
			case WM_SETFOCUS:
				CheckDlgButton(hDlg, IDC_BUTTON1, BS_DEFPUSHBUTTON);

			case WM_COMMAND:
			{
				switch LOWORD(wParam)
				{

				case IDC_BUTTON1:
				{
					SetFocus(hDlg);
					CheckDlgButton(hDlg, IDC_BUTTON1, BS_DEFPUSHBUTTON);
					if (HIWORD(wParam) == BN_CLICKED)
					{
						LPCTSTR lpszText2 = TEXT("\nШаг 2: Стартовый текст\n");
						lstrcpy(buf, lpszText2);

						SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), buf);
						return (INT_PTR)TRUE;

					}


				}

				case IDC_BUTTON2:
				{
					SetFocus(hDlg);
					CheckDlgButton(hDlg, IDC_BUTTON1, BS_DEFPUSHBUTTON);

					if (HIWORD(wParam) == BN_CLICKED)
					{
						LPCTSTR lpszText3 = TEXT("\nШаг 3: Загружено в буфер\n");
						lstrcat(Buffer, lpszText3);

						//HANDLE hf = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						//Иницализация OPENFILENAME
						ZeroMemory(&ofn, sizeof(OPENFILENAME));
						ofn.lStructSize = sizeof(OPENFILENAME);
						ofn.hwndOwner = hWnd;  // hwnd – дескриптор окна–влвдельца
						ofn.lpstrFile = FileName;
						ofn.lpstrFile[0] = '\0';
						ofn.nMaxFile = sizeof(FileName);

						// Формирование массива строк шаблонов фильтра
						ofn.lpstrFilter = TEXT("All\0*.*\0Text\0*.TXT\0");
						ofn.nFilterIndex = 1; // Индекс для текущего шаблона фильтра
						ofn.lpstrFileTitle = NULL; // Без заголовка
						ofn.nMaxFileTitle = 0;
						ofn.lpstrInitialDir = NULL; // В качестве начального текущий каталог
						ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

						// Отображение диалогового окна 
						BOOL fRet = GetOpenFileName(&ofn);
						if (fRet == FALSE) return 1;//ошибка в далоге 
						hf = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL);

						//Проверка корректности открытия файла
						if (hf == INVALID_HANDLE_VALUE) return (-1);

						//Чтение из файла в буфер

						DWORD dwNumbOfBytes;
						ReadFile(hf, Buffer, MAX_BYTES, &dwNumbOfBytes, NULL);

						SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), Buffer);
						if (hf) CloseHandle(hf);						
						return (INT_PTR)TRUE;
						break;
					}
				}

				case IDOK:
				{
					EndDialog(hDlg, LOWORD(wParam));
				}
				break;
				
				case WM_DESTROY:
				{
					EndDialog(hDlg, LOWORD(wParam));
					break;
				}
				}
			

			}return (INT_PTR)TRUE;

			

			}return (INT_PTR)FALSE;
            
           
		}

		INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
		{
			UNREFERENCED_PARAMETER(lParam);
			
			switch (message)
			{
				HANDLE_MSG(hDlg, WM_INITDIALOG, DlgProc_OnInitDialog);
				HANDLE_MSG(hDlg, WM_COMMAND, DlgProc_OnCommand1);
			
				return (INT_PTR)TRUE;

			}
			return (INT_PTR)FALSE;
		}

		BOOL DlgProc_OnInitDialog(HWND hDlg, HWND fokus, LPARAM lParam)
		{
			SYSTEMTIME st;
			GetLocalTime(&st);

			TCHAR buf1[300] = TEXT("");
			TCHAR buf[500] = TEXT("");

			LPCTSTR lpszText1 = TEXT("Сведения о программе:\n");
			LPCTSTR lpszText2 = TEXT("\nАвтор<Сендецкая И.В., 50321-2>\n");
			lstrcat(buf, lpszText1);
			lstrcat(buf, lpszText2);
			wsprintf(buf1, TEXT("Run time=День-%d, Месяц-%d, Год-%d, Время-%d:%d:%d"), st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
			lstrcat(buf, buf1);

			SetWindowText(GetDlgItem(hDlg, IDC_STATIC11), buf);

			return (INT_PTR)TRUE;
		}
		void DlgProc_OnCommand1(HWND hDlg, int wmld, HWND hWnd1, UINT wmEvent)
		{
			switch (wmld)
			{

			case IDOK:
			{
				EndDialog(hDlg, wmld);
			}
			break;
			}
		}

		INT_PTR CALLBACK bmpProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
			
		{
			UNREFERENCED_PARAMETER(lParam);
			switch (message)
			{

			case WM_INITDIALOG:

				ShowWindow(hDlg, SW_SHOW);
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
				case IDC_LOAD_IMAGE:
				{
					HDC hDC;
					HDC hMemDC;
					HANDLE hBmp;
					HANDLE hOldBmp;
					BITMAP Bmp;
					hBmp = LoadImage(NULL, "11.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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
				}
				break;
				}
			}
			return (INT_PTR)FALSE;
		}
