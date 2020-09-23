#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <string.h>



LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

LPCTSTR g_lpszClassName = TEXT("sp_pr2_sr_class"); //имя класса
LPCTSTR g_lpszAplicationTitle = TEXT("Цвета радуги. Программист <Яцкевич, Павел>");

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
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));    
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 7);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Ошибка регистрации класса окна!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hWnd = CreateWindowEx(NULL, g_lpszClassName, g_lpszAplicationTitle, WS_OVERLAPPEDWINDOW, 0, 0, 700, 700, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	while (GetMessage(&msg, (HWND)NULL, 0, 0))

	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
// Оконная процедура

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

{

	int wmld, wmEvent;
	HDC hdc;

	
	static HWND hButtonAdd;
	static HWND hButtonExit;
	static HWND hStat;
	static HWND hListBox;


#define IDC_BTN_ADD 101
#define IDC_LISTBOX 103

	

	switch (msg)
	{
	case WM_CREATE:
	{

					  if (!(hStat = CreateWindowEx(0L, TEXT("static"), TEXT("Результат"), WS_CHILD | WS_CAPTION | WS_VISIBLE | WS_SIZEBOX,
						  300, 50, 150, 80, hWnd, (HMENU)0, hInstance, NULL))) return (-1);
					  

					  if (!(hListBox = CreateWindowEx(0L, TEXT("ListBox"), TEXT("Список цветов радуги"), WS_CHILD | WS_CAPTION | WS_VISIBLE | WS_SIZEBOX | 
						  WS_HSCROLL | WS_VSCROLL, 20, 50, 160, 250, hWnd, (HMENU)(IDC_LISTBOX), hInstance, NULL))) return (-1);

					  

					  SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("красный"));
					  SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("оранжевый"));
					  SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("желтый"));
					  SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("зеленый"));
					  SendMessage(hListBox, LB_ADDSTRING,0, (LPARAM)TEXT("голубой"));
					  SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("синий"));
					  SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("фиолетовый"));
					  

					  SendMessage(hListBox, LB_SETCURSEL, (WPARAM)0, 0L);

					 // if (!(hButtonSave = CreateWindowEx(0L, TEXT("Button"), TEXT("В буфер"), WS_CHILD | WS_BORDER | WS_VISIBLE, 20, 240, 80, 24, hWnd, 
						//  (HMENU)(IDC_BTN_SAVE), NULL, NULL))) return (-1);

					  if (!(hButtonAdd = CreateWindowEx(0L, TEXT("Button"), TEXT("Отобразить"), WS_CHILD | WS_BORDER | WS_VISIBLE, 120, 350, 90, 30, hWnd,
						  (HMENU)(IDC_BTN_ADD), hInstance, NULL))) return (-1);

					  if (!(hButtonExit = CreateWindowEx(0L, TEXT("Button"), TEXT("Выход"), WS_CHILD | WS_BORDER | WS_VISIBLE, 250, 350, 90, 30, hWnd,
						  (HMENU)(IDCANCEL), hInstance, NULL))) return (-1);

	}
		return 0;

	case WM_COMMAND:
	{
					   
					   wmld = LOWORD(wParam);
					   wmEvent = HIWORD(wParam);
					   static TCHAR str[500];

					   switch (wmld)
					   {

					   case IDCANCEL:
						   DestroyWindow(hWnd);
						   break;

					   case IDC_BTN_ADD:
					   {
										   if (LOWORD(wParam) == IDC_BTN_ADD)
										   {
										   SetWindowText(hStat, (LPCWSTR)"\0");
										   SetFocus(hListBox);
								           int itemIndex = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0L);   //получение номера выделенной строки
								  		   SendMessage(hListBox, LB_GETTEXT, itemIndex, LPARAM(str));        //сохранение в буфере выделенного текста
										  
										   
										   switch (itemIndex)
											   {
										   case 0:
											{	
                                               SetWindowText(hStat, str);
											   HDC hdc = GetDC(hStat);
										       SetTextColor(hdc, RGB(255,0,0));											   										 
											   TextOut(hdc,NULL,NULL,str,25);
											   ReleaseDC(hStat,hdc);
											   
										   } break;
										   case 1:
										   {
													 SetWindowText(hStat, str);
													 HDC hdc = GetDC(hStat);
													 SetTextColor(hdc, RGB(255, 125, 0));
													 TextOut(hdc, NULL, NULL, str, 25);
													 ReleaseDC(hStat, hdc);

										   } break;
										   case 2:
										   {
													 SetWindowText(hStat, str);
													 HDC hdc = GetDC(hStat);
													 SetTextColor(hdc, RGB(255, 255, 0));
													 TextOut(hdc, NULL, NULL, str, 25);
													 ReleaseDC(hStat, hdc);

										   } break;
										   case 3:
										   {
													 SetWindowText(hStat, str);
													 HDC hdc = GetDC(hStat);
													 SetTextColor(hdc, RGB(0, 255, 0));
													 TextOut(hdc, NULL, NULL, str, 25);
													 ReleaseDC(hStat, hdc);

										   } break;
										   case 4:
										   {
													 SetWindowText(hStat, str);
													 HDC hdc = GetDC(hStat);
													 SetTextColor(hdc, RGB(0, 255, 255));
													 TextOut(hdc, NULL, NULL, str, 25);
													 ReleaseDC(hStat, hdc);

										   } break;
										   case 5:
										   {
													 SetWindowText(hStat, str);
													 HDC hdc = GetDC(hStat);
													 SetTextColor(hdc, RGB(0, 0, 255));
													 TextOut(hdc, NULL, NULL, str, 25);
													 ReleaseDC(hStat, hdc);

										   } break;
										   case 6:
										   {
													 SetWindowText(hStat, str);
													 HDC hdc = GetDC(hStat);
													 SetTextColor(hdc, RGB(125, 0, 255));
													 TextOut(hdc, NULL, NULL, str, 25);
													 ReleaseDC(hStat, hdc);

										   } break;

										   default:
											   return(DefWindowProc(hWnd, msg, wParam, lParam));
								               }
										   }

										   
					   } break;

					   default:
						   return(DefWindowProc(hWnd, msg, wParam, lParam));
					   }
	} break;


	case WM_PAINT:    // Вывод при обновлении окна (перерисовка)
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);  // Получение контекста для	
		TextOut(hdc, 50, 10, TEXT("Выберите любой цвет:"), 20);
		EndPaint(hWnd, &ps); // Завершение обновления окна
		break;


	case WM_DESTROY:  // Завершение работы приложения
		PostQuitMessage(IDCANCEL); // Посылка WM_QUIT приложению
		break;
	default: // Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;// Для ветвей с "break"

}
