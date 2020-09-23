#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265359

LRESULT CALLBACK Pr6_WndProc(HWND, UINT, WPARAM, LPARAM);

LPCTSTR g_lpszClassName = TEXT("sp_pr7_class"); //имя класса
LPCTSTR g_lpszAplicationTitle = TEXT("Метафайл. Программист <Яцкевич, Павел>");

static HMETAFILE hmf;
HDC hdc;

HINSTANCE g_hInstance;
HDC g_hdc;

BOOL WndProc_OnCreate(HWND, LPCREATESTRUCT);
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
	static HMETAFILE hmf;
	

	switch (msg)
	{
		HANDLE_MSG(hWnd, WM_CREATE, WndProc_OnCreate);
		HANDLE_MSG(hWnd, WM_PAINT, WndProc_OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, WndProc_OnDestroy);
	default: // Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;

}

BOOL WndProc_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	HDC hdcMeta = CreateMetaFile(NULL);
	//задание 1: вывод текста ФИО
	static LOGFONT lf;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfPitchAndFamily = DEFAULT_PITCH;
	lstrcpy(lf.lfFaceName, TEXT("Microsoft Sans Serif"));
	lf.lfHeight = MulDiv(36, GetDeviceCaps(hdcMeta, 1), 72);
	lf.lfItalic = 1;
	lf.lfWeight = FW_BOLD;
	HFONT HNewFont = CreateFontIndirect(&lf);
	HFONT HOldFont = (HFONT)SelectObject(hdcMeta, HNewFont);
	SetTextColor(hdcMeta, RGB(255, 0, 0));
	SetBkMode(hdcMeta, TRANSPARENT);
	TextOut(hdcMeta, 10, 10, TEXT("Яцкевич Павел Константинович"), 28);
	SelectObject(hdcMeta, HOldFont);
	DeleteObject(HNewFont);

	//задание 2: вывод графической фигуры звезда
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));

	SelectObject(hdcMeta, hPen);
	SelectObject(hdcMeta, hBrush);

	static int xc = 200, yc = 200;
	static int r = 80;


	POINT pt[5] = {};
	pt[0].x = xc;
	pt[0].y = yc - r;
	pt[1].x = (int)(xc + r*sin((double)(2.*PI * 0, 1)));
	pt[1].y = (int)(yc + r*cos((double)(2.*PI * 0, 1)));
	pt[2].x = (int)(xc - r*sin((double)(2.*PI * 0, 2)));
	pt[2].y = (int)(yc + r*cos((double)(2.*PI * 0, 2)));
	pt[3].x = (int)(xc + r*sin((double)(2.*PI * 0, 2)));
	pt[3].y = (int)(yc + r*cos((double)(2.*PI * 0, 2)));
	pt[4].x = (int)(xc - r*sin((double)(2.*PI * 0, 1)));
	pt[4].y = (int)(yc + r*cos((double)(2.*PI * 0, 1)));

	MoveToEx(hdcMeta, pt[0].x, pt[0].y, (LPPOINT)NULL);
	for (int i = 1; i < 5; i++)
		LineTo(hdcMeta, pt[i].x, pt[i].y);
	SetPolyFillMode(hdcMeta, WINDING);
	Polygon(hdcMeta, pt, 5);

	DeleteObject(hPen);
	DeleteObject(hBrush);
	hmf = CloseMetaFile(hdcMeta);
	
	return true;
}

void WndProc_OnPaint(HWND hWnd)
{// Вывод при обновлении окна (перерисовка)
	
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);  // Получение контекста для
	
	for (int x = 0; x < 5; x++)
		for (int y = 0; y < 5; y++)
		{
			SetWindowOrgEx(hdc, -100 * x, -100 * y, NULL);
			PlayMetaFile(hdc, hmf);
		}
	EndPaint(hWnd, &ps); // Завершение обновления окна
}

void WndProc_OnDestroy(HWND hWnd)
{  // Завершение работы приложения
	DeleteMetaFile(hmf);
	PostQuitMessage(0); // Посылка WM_QUIT приложению
}
