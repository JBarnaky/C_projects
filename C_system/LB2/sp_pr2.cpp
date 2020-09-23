#include <windows.h>
#include <tchar.h>


LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

LPCTSTR g_lpszClassName = TEXT("sp_pr2_class"); //имя класса
LPCTSTR g_lpszAplicationTitle = TEXT("Главное окно приложения. Программист <Яцкевич, Павел>");
LPCTSTR g_lpszDestroyMessage = TEXT("Разрушается окно. В связи с этим поступило сообщение WM_DESTROY, из обработчика которого и выполнен данный вывод.");
LPCTSTR g_lpszLButDownMessage = TEXT("Обработка сообщения WM_LBUTTONDOWN, которое посылается в окно при щелчке левой кнопки мыши");
LPCTSTR g_lpszPaintMessage = TEXT("Вывод текста при обработке сообщения WM_PAINT. Это сообщение окно получает после того, как оно было закрыто другим окном и затем открыто");
LPCTSTR g_lpszCreateMessage = TEXT("Выполняется обработка WM_CREATE");

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
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ASTERISK));    //установить иконку как IDI_ASTERISK 
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(0, 255, 0)));   //Варианты цвета в формате  R, G, B   0,255,0
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Ошибка регистрации класса окна!"),TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hWnd = CreateWindowEx(NULL, g_lpszClassName, g_lpszAplicationTitle, (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX), //WS_OVERLAPPEDWINDOW без флага MAXIMIZEBOX
		0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (!hWnd)
     {
		MessageBox(NULL, TEXT("Окно не создано!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))

	{
		DispatchMessage(&msg);
    }

	return msg.wParam;
}
// Оконная процедура

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

{
	HDC hdc;
	switch (msg)
	{
	case WM_CREATE:    
		
		if (!hWnd)
			return -1;
		else
		{
			CreateWindowEx;
			MessageBox(NULL, g_lpszCreateMessage, g_lpszAplicationTitle, MB_OK);
			return 0;
		}
		break;

	case WM_PAINT:    // Вывод при обновлении окна (перерисовка)
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);  // Получение контекста для
		// обновления окна   
		TextOut(hdc, 20, 100, g_lpszPaintMessage, 100); // Вывод в контекст
		EndPaint(hWnd, &ps); // Завершение обновления окна
		break;

	case WM_LBUTTONDOWN:
	{
		hdc = GetDC(hWnd);
		RECT re;

		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		GetClientRect(hWnd, &re);
		SetTextColor(hdc, 0x00000000);
		SetBkMode(hdc, TRANSPARENT);

		re.left = x;
		re.top = y;

		DrawText(hdc, g_lpszLButDownMessage, -1, &re, DT_SINGLELINE | DT_NOCLIP);
		//TextOut(hdc, 50, 200, g_lpszLButDownMessage, 100);
		ReleaseDC(hWnd, hdc);
		break;
	}

	case WM_DESTROY:  // Завершение работы приложения
		MessageBox(NULL, g_lpszDestroyMessage, g_lpszAplicationTitle, MB_OK); //сообщение при завершении приложения
		PostQuitMessage(12); // Посылка WM_QUIT приложению
		break;

	default: // Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return FALSE;// Для ветвей с "break"

}
