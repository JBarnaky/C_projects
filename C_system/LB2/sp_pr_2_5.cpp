#include <windows.h>
#include <windowsx.h>
#include <tchar.h>


LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

LPCTSTR g_lpszClassName = TEXT("sp_pr2_class"); //��� ������
LPCTSTR g_lpszAplicationTitle = TEXT("������� ���� ����������. ����������� <�������, �����>");
LPCTSTR g_lpszDestroyMessage = TEXT("����������� ����. � ����� � ���� ��������� ��������� WM_DESTROY, �� ����������� �������� � �������� ������ �����.");
LPCTSTR g_lpszPaintMessage = TEXT("����� ������ ��� ��������� ��������� WM_PAINT. ��� ��������� ���� �������� ����� ����, ��� ��� ���� ������� ������ ����� � ����� �������");


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
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));    //���������� ������ ��� IDI_ASTERISK 
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("������ ����������� ������ ����!"), TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hWnd = CreateWindowEx(NULL, g_lpszClassName, g_lpszAplicationTitle, (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX), //WS_OVERLAPPEDWINDOW ��� ����� MAXIMIZEBOX
		0, 0, 700, 700, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("���� �� �������!"), TEXT("������"), MB_OK | MB_ICONERROR);
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
// ������� ���������

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

{
	
	int wmld, wmEvent;
	HDC hdc;

	static HWND hButtonSave;
	static HWND hButtonAdd;
	static HWND hButtonExit;
	static HWND hEdit;
	static HWND hListBox;

#define IDC_BTN_SAVE 100
#define IDC_BTN_ADD 101
#define IDC_EDIT1 102
#define IDC_LISTBOX 103


	switch (msg)
	{
	case WM_CREATE:
	{

					  if (!(hEdit = CreateWindowEx(0L, TEXT("Edit"), TEXT("��������"), WS_CHILD | WS_BORDER | WS_VISIBLE, 20, 50, 160, 40, hWnd, (HMENU)(IDC_EDIT1), NULL, NULL)))
						  return (-1);
					  

					  if (!(hListBox = CreateWindowEx(0L, TEXT("ListBox"), TEXT("������"), WS_CHILD | WS_BORDER | WS_VISIBLE, 200, 50, 160, 180, hWnd, (HMENU)(IDC_LISTBOX), NULL, NULL)))
						  return (-1);
					  
					  if (!(hButtonSave = CreateWindowEx(0L, TEXT("Button"), TEXT("� �����"), WS_CHILD | WS_BORDER | WS_VISIBLE, 20, 240, 80, 24, hWnd, (HMENU)(IDC_BTN_SAVE), NULL, NULL)))
						  return (-1);
					 
					  if (!(hButtonAdd = CreateWindowEx(0L, TEXT("Button"), TEXT("� ������"), WS_CHILD | WS_BORDER | WS_VISIBLE, 120, 240, 80, 24, hWnd, (HMENU)(IDC_BTN_ADD), NULL, NULL)))
						  return (-1);
					  
					  if (!(hButtonExit = CreateWindowEx(0L, TEXT("Button"), TEXT("�����"), WS_CHILD | WS_BORDER | WS_VISIBLE, 220, 240, 80, 24, hWnd, (HMENU)(IDCANCEL), NULL, NULL)))
						  return (-1);
					 
	}
		return 0;

	case WM_COMMAND:
	{
					   wmld = LOWORD(wParam);
					   wmEvent = HIWORD(wParam);
					   static TCHAR pszTextBuff[500];

					   switch (wmld)
					   {

					   case IDCANCEL:
						   DestroyWindow(hWnd);
						   break;

					   case IDC_BTN_SAVE:
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

					   case IDC_BTN_ADD:
					   {
										   int ind = SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)pszTextBuff);
										   if (ind == LB_ERR)
											   MessageBox(hWnd, TEXT("������ � ������"), TEXT(""), MB_OK);

					   } break;

					   default:
						   return(DefWindowProc(hWnd, msg, wParam, lParam));
					   }
	} break;


	case WM_PAINT:    // ����� ��� ���������� ���� (�����������)
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);  // ��������� ��������� ���
		// ���������� ����   
		TextOut(hdc, 20, 100, g_lpszPaintMessage, 100); // ����� � ��������
		EndPaint(hWnd, &ps); // ���������� ���������� ����
		break;



	case WM_DESTROY:  // ���������� ������ ����������
		MessageBox(NULL, g_lpszDestroyMessage, g_lpszAplicationTitle, MB_OK); //��������� ��� ���������� ����������
		PostQuitMessage(5); // ������� WM_QUIT ����������
		break;
	default: // ����� "����������� �� ���������"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;// ��� ������ � "break"

}