#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265359

LRESULT CALLBACK Pr6_WndProc(HWND, UINT, WPARAM, LPARAM);

LPCTSTR g_lpszClassName = TEXT("sp_pr7_class"); //имя класса
LPCTSTR g_lpszAplicationTitle = TEXT("Графический вывод. Программист <Яцкевич, Павел>");

HINSTANCE g_hInstance;
HDC g_hdc;

//void WndProc_OnMouseMove(HWND, int, int, UINT);
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
		//HANDLE_MSG(hWnd, WM_MOUSEMOVE, WndProc_OnMouseMove);
		HANDLE_MSG(hWnd, WM_PAINT, WndProc_OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, WndProc_OnDestroy);
	default: // Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;

}

//void WndProc_OnMouseMove(HWND hWnd, int x, int y, UINT keyFlags)
//{
//	BOOL fDraw = 0;
//	static TCHAR buf[100];
//	BOOL fPrevLine = FALSE;
//	static POINTS ptsBegin;
//	static POINTS ptsEnd;
//	static POINTS ptsPrevEnd;
//
//	HDC DC = GetDC(hWnd);
//
//	wsprintf(buf, TEXT("WM_MOUSEMOVE x = %d y = %d"), x, y);
//	TextOut(DC, 10, 10, buf, lstrlen(buf));
//
//	if (keyFlags == MK_LBUTTON)
//	{
//		DWORD xyPos = GetMessagePos();
//		WORD xPos = LOWORD(xyPos), yPos = HIWORD(xyPos);
//
//		MoveToEx(DC, xPos, yPos, (LPPOINT)NULL);
//		LineTo(DC, x, y);
//
//	}
//	ReleaseDC(hWnd, DC);
//}

void WndProc_OnPaint(HWND hWnd)
{// Вывод при обновлении окна (перерисовка)
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);  // Получение контекста для

	//задание 1: вывод текста ФИО
	static LOGFONT lf;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfPitchAndFamily = DEFAULT_PITCH;
	lstrcpy(lf.lfFaceName, TEXT("Microsoft Sans Serif"));
	lf.lfHeight=MulDiv(36,GetDeviceCaps(hdc,1),72);
	lf.lfItalic = 1;
	lf.lfWeight = FW_BOLD;
	HFONT HNewFont = CreateFontIndirect(&lf);
	HFONT HOldFont = (HFONT)SelectObject(hdc, HNewFont);
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkMode(hdc,TRANSPARENT);
	TextOut(hdc, 10, 10, TEXT("Яцкевич Павел Константинович"), 28);
	SelectObject(hdc, HOldFont);
	DeleteObject(HNewFont);

	//задание 2: вывод графической фигуры звезда
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));

	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);

	static int xc = 200, yc = 200;
	static int r = 80;
	
	
	POINT pt[5] = { };
	pt[0].x = xc;
	pt[0].y = yc-r;
	pt[1].x = (int)(xc + r*sin((double)(2.*PI * 0, 1)));
	pt[1].y = (int)(yc + r*cos((double)(2.*PI * 0, 1)));
	pt[2].x = (int)(xc - r*sin((double)(2.*PI * 0, 2)));
	pt[2].y = (int)(yc + r*cos((double)(2.*PI * 0, 2)));
	pt[3].x = (int)(xc + r*sin((double)(2.*PI * 0, 2)));
	pt[3].y = (int)(yc + r*cos((double)(2.*PI * 0, 2)));
	pt[4].x = (int)(xc - r*sin((double)(2.*PI * 0, 1)));
	pt[4].y = (int)(yc + r*cos((double)(2.*PI * 0, 1)));

	MoveToEx(hdc, pt[0].x, pt[0].y, (LPPOINT)NULL);
	for (int i = 1; i < 5;i++)
		LineTo(hdc, pt[i].x, pt[i].y);
	SetPolyFillMode(hdc, WINDING);
	Polygon(hdc, pt, 5);
	

	DeleteObject(hPen);
	DeleteObject(hBrush);
	EndPaint(hWnd, &ps); // Завершение обновления окна
}

void WndProc_OnDestroy(HWND hWnd)
{  // Завершение работы приложения
	PostQuitMessage(0); // Посылка WM_QUIT приложению
}