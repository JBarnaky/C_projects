#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <string.h>

LRESULT CALLBACK Pr6_WndProc(HWND, UINT, WPARAM, LPARAM);

LPCTSTR g_lpszClassName = TEXT("sp_pr6_class"); //имя класса
LPCTSTR g_lpszAplicationTitle = TEXT("Обработка сообщений мыши и клавиатуры. Программист <Яцкевич, Павел>");

HINSTANCE g_hInstance;
HDC g_hdc;

void WndProc_OnMouseMove(HWND, int, int, UINT);
//void WndProc_OnLButtonDown(HWND, BOOL, int, int, UINT);
void WndProc_OnPaint(HWND);
void WndProc_OnDestroy(HWND);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)

{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;
	g_hInstance = hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = Pr6_WndProc;
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



LRESULT CALLBACK Pr6_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

{
	switch (msg)
	{
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, WndProc_OnMouseMove);
		HANDLE_MSG(hWnd, WM_PAINT, WndProc_OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, WndProc_OnDestroy);
	default: // Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;

}

void WndProc_OnMouseMove(HWND hWnd, int x, int y, UINT keyFlags)
{
	BOOL fDraw = 0;
	static TCHAR buf[100];
	BOOL fPrevLine = FALSE;
	static POINTS ptsBegin;       
	static POINTS ptsEnd;
	static POINTS ptsPrevEnd;
	
	HDC DC = GetDC(hWnd);
	
	wsprintf(buf, TEXT("WM_MOUSEMOVE x = %d y = %d"), x, y);
	TextOut(DC, 10, 10, buf, lstrlen(buf));

	if (keyFlags == MK_LBUTTON)
	{
		DWORD xyPos = GetMessagePos();
		WORD xPos = LOWORD(xyPos), yPos = HIWORD(xyPos);
		
		//SetROP2(DC, R2_NOTXORPEN);

		MoveToEx(DC, xPos, yPos, (LPPOINT)NULL);
		LineTo(DC, x, y);
	}
	ReleaseDC(hWnd, DC);
}

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