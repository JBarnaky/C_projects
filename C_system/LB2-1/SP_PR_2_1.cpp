// SP_PR_2_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SP_PR_2_1.h"
#include <shellapi.h>
#include <stdio.h>
#include <commdlg.h>

#define MAX_BYTES  10000
#define ID_3_EDIT 3320

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT_PTR CALLBACK DlgInfo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void OpenFileDialog(HWND hwnd);

TCHAR FileName[250];
LPTSTR FileName1 = TEXT("1.bmp");
DWORD dwNumbOfBytes = MAX_BYTES;

TCHAR Buffer[MAX_BYTES];
HANDLE hf = NULL;
//OPENFILENAME ofn;
HWND hWnd;



HANDLE ProcHandle[4];   //для дескрипторов процессов;
//HANDLE ProcCalc;
DWORD  ProcId[4];    //для идентификаторов процессов;
HANDLE ThreadHandle[4];  //для дескрипторов потоков;
DWORD  ThreadId[4];  //для идентификаторов потоков;
LPTSTR   ProcImage[4] = { 0, TEXT("C:\\Windows\\Notepad.exe"), TEXT("C:\\Windows\\Notepad.exe"), TEXT("C:\\Windows\\System32\\calc.exe") }; //для указателей строк, идентифицирущих файлы запускаемых программ;
TCHAR   CmdParam[4][260] = { 0, 0, 0, 0 }; //для строк c параметрами запускаемых программ



// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_SP_PR_2_1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SP_PR_2_1));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SP_PR_2_1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SP_PR_2_1);
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

   hWnd = CreateWindow(szWindowClass, TEXT("SP-LB2-1 Яцкевич П.К. Гр. 60322-1"), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 600, 500, NULL, NULL, hInstance, NULL);

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

	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx(NULL, TEXT("Edit"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 100, 400, 100, hWnd, (HMENU)ID_3_EDIT, NULL, NULL);


		static TCHAR Buf1[260];
		GetModuleFileName(NULL, Buf1, 260);
		ProcImage[0] = Buf1;
		ProcHandle[0]=GetCurrentProcess();
		ProcId[0] = GetProcessId(GetCurrentProcess());

	}return 0;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
			//////////////////////////////////////////////////////////////
		case IDM_PROC_NOTE:
		{
			STARTUPINFO si;
			ZeroMemory(&si, sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO);

			PROCESS_INFORMATION pi;
			ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

			SECURITY_ATTRIBUTES sp, st;
			sp.nLength = sizeof(SECURITY_ATTRIBUTES);
			sp.lpSecurityDescriptor = NULL;
			sp.bInheritHandle = FALSE;

			st.nLength = sizeof(SECURITY_ATTRIBUTES);
			st.lpSecurityDescriptor = NULL;
			st.bInheritHandle = FALSE;

			if (!CreateProcess(ProcImage[1], NULL, &sp, &st, FALSE, 0, NULL, NULL, &si, &pi))        //
			{
				MessageBox(hWnd, TEXT("Ошибка запуска процесса!"), NULL, MB_OK);
				break;
			}

			//Создание глобальных массивов
			else
			{
				ProcHandle[1] = pi.hProcess;
				ProcId[1] = pi.dwProcessId;
				ThreadHandle[1] = pi.hThread;
				ThreadId[1] = pi.dwThreadId;
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
			
		}break;

		//   Другой процесс..........................
		case IDM_PROC_NOTE_WTEXT:
		{
			OpenFileDialog(hWnd);
			SECURITY_ATTRIBUTES sp, st;
			sp.bInheritHandle = FALSE;
			sp.lpSecurityDescriptor = NULL;
			sp.nLength = sizeof(SECURITY_ATTRIBUTES);
			st.bInheritHandle = FALSE;
			st.lpSecurityDescriptor = NULL;
			st.nLength = sizeof(SECURITY_ATTRIBUTES);
			STARTUPINFO si;
			ZeroMemory(&si, sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO);
			TCHAR PATCH[260] = { TEXT("notepad ") };
			PROCESS_INFORMATION pi;
			lstrcat(PATCH, FileName);
			if (!CreateProcess(NULL, PATCH, &sp, &st, FALSE, 0, NULL, NULL, &si, &pi))
			{
				MessageBox(hWnd, TEXT("Ошибка запуска процесса"), NULL, MB_ICONERROR | MB_OK);
			}
			else
			{
				ProcHandle[2] = pi.hProcess;
				ThreadHandle[2] = pi.hThread;
				ProcId[2] = pi.dwProcessId;
				ThreadId[2] = pi.dwThreadId;

			}
			WaitForSingleObject(pi.hProcess, INFINITE);
			hf = CreateFile(FileName, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
			
			//Проверка корректности открытия файла
			if (hf == INVALID_HANDLE_VALUE)
			{
				MessageBox(hWnd, TEXT("Не возможно открыть файл"), TEXT("Ошибка"), MB_ICONERROR | MB_OK);
			}

			else
			{
				ReadFile(hf, Buffer, MAX_BYTES, &dwNumbOfBytes, NULL);
				TCHAR Buff[260];
				TCHAR Buff1[260];
				AnsiToOem ((LPSTR)Buffer, (LPSTR)Buff);
				OemToChar((LPSTR)Buff,Buff1);
				SetDlgItemText(hWnd, ID_3_EDIT, Buff1);

				CloseHandle(hf);
			}
			break;
		}

		///////////////////////////////////////////
		case IDM_PROC_CALC:
		{
			STARTUPINFO si;
			ZeroMemory(&si, sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO);

			PROCESS_INFORMATION pi;

			ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

			SECURITY_ATTRIBUTES sp, st;
			sp.nLength = sizeof(SECURITY_ATTRIBUTES);
			sp.lpSecurityDescriptor = NULL;
			sp.bInheritHandle = FALSE;

			st.nLength = sizeof(SECURITY_ATTRIBUTES);
			st.lpSecurityDescriptor = NULL;
			st.bInheritHandle = FALSE;

			if (!CreateProcess(ProcImage[3], NULL, &sp, &st, FALSE, 0, NULL, NULL, &si, &pi))        //
			{
				MessageBox(hWnd, TEXT("Ошибка запуска процесса!"), NULL, MB_OK);
				break;
			}


			else
			{
				ProcHandle[3] = pi.hProcess;
				ProcId[3] = pi.dwProcessId;
				ThreadHandle[3] = pi.hThread;
				ThreadId[3] = pi.dwThreadId;
				/*CloseHandle(pi.hProcess);*/
				/*CloseHandle(pi.hThread);*/
			}

		}break;

		/////////////////////////////////////
		case IDM_PROC_EXIT_CALC:
		{	
			HANDLE OP;
		OP = OpenProcess(PROCESS_ALL_ACCESS , FALSE, ProcId[3]);
		if (OP == 0)
		{
			MessageBox(hWnd, TEXT("Не открыт процесс!"), TEXT("Ошибка"), MB_OK);
		}
		else
		{
			BOOL f=TerminateProcess(OP, 12);
			if (!f)
			{
				MessageBox(hWnd, TEXT("Не выполнено закрытие процесса!"), TEXT("Ошибка"), MB_OK);
			}
		}
		}
	        break;


		/////////////////////////////////////////////////////
		case IDM_TestProc:
		{
			SECURITY_ATTRIBUTES sp, st;
			sp.bInheritHandle = FALSE;
			sp.lpSecurityDescriptor = NULL;
			sp.nLength = sizeof(SECURITY_ATTRIBUTES);
			st.bInheritHandle = FALSE;
			st.lpSecurityDescriptor = NULL;
			st.nLength = sizeof(SECURITY_ATTRIBUTES);

			STARTUPINFO si;
			ZeroMemory(&si, sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO);

			si.dwFlags = STARTF_USEPOSITION | STARTF_USESHOWWINDOW;
			si.dwX = 100;
			si.dwY = 100;
			si.wShowWindow = SW_SHOWMAXIMIZED;


			PROCESS_INFORMATION pi;

			if (!CreateProcess(TEXT("C:\\учеба\\сп\\SP_PR_2_1\\TestProc\\TestProc\\SP_PR7.exe"), NULL, &sp, &st, FALSE, 0, NULL, NULL, &si, &pi))
			{
				MessageBox(hWnd, TEXT("Ошибка запуска процесса"), NULL, MB_ICONERROR | MB_OK);
			}

			break;
		}



		//информация
		case IDM_INFO_CUR:   //текущий процесс
		{
		  DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfo, 0);
		}break;

		case IDM_INFO_NOTE:  //блокнот
		{
			DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfo, 1);
		}break;

		case IDM_INFO_NOTE_WTEXT:  //блокнот с текстом
		{
			DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfo, 2);
		}break;


		case IDM_INFO_CALC:  //калькулятор
		{
			DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgInfo, 3);
		}break;

		

//////////////////////////////////////////////////////////////
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

INT_PTR CALLBACK DlgInfo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		///////////////////////////////
	   SetDlgItemText(hDlg, IDC_EDIT1, ProcImage[lParam]);

		TCHAR Buf[200];

		wsprintf(Buf, TEXT("0x%08X"), ProcHandle[lParam]);
		SetDlgItemText(hDlg, IDC_EDIT2, Buf);

		wsprintf(Buf, TEXT("%d"), ProcId[lParam]);
		SetDlgItemText(hDlg, IDC_EDIT3, Buf);

		wsprintf(Buf, TEXT("%d"), ThreadHandle[lParam]);
		SetDlgItemText(hDlg, IDC_EDIT4, Buf);

		wsprintf(Buf, TEXT("%d"), ThreadId[lParam]);
		SetDlgItemText(hDlg, IDC_EDIT5, Buf);


		///////////////////////////////////////////
		DWORD dwExitCode;
		if (!GetExitCodeProcess(ProcHandle[lParam], &dwExitCode))
		{
			DWORD ErrCode = GetLastError();
			wsprintf(Buf, TEXT("Ошибка GECP код= %d"), ProcHandle[lParam], ErrCode);
		}
		else
		{
			if (dwExitCode == STILL_ACTIVE)
			{
				wsprintf(Buf, TEXT("Процесс не завершился!"));
			}
			else
			{
				wsprintf(Buf, TEXT("%d"), dwExitCode);
			}
			SetDlgItemText(hDlg, IDC_EDIT6, Buf);
		}
///////////////////////////////////////////////////////////
		///////////////////////////////////////////
		DWORD dwExitCode1;
		if (!GetExitCodeThread(ThreadHandle[lParam], &dwExitCode1))
		{
			DWORD ErrCode = GetLastError();
			wsprintf(Buf, TEXT("Ошибка GECP код= %d"), ThreadHandle[lParam], ErrCode);
		}
		else
		{
			if (dwExitCode1 == STILL_ACTIVE)
			{
				wsprintf(Buf, TEXT("Состояние - Активен!"));
			}
			else
			{
				wsprintf(Buf, TEXT("%d"), dwExitCode1);
			}
			SetDlgItemText(hDlg, IDC_EDIT7, Buf);
		}
		///////////////////////////////////////////////////////////
		
		wsprintf(Buf, TEXT("%d"), GetPriorityClass(ProcHandle[lParam]));
		SetDlgItemText(hDlg, IDC_EDIT8, Buf);

		///////////////////////////////////////////////////////////////

		FILETIME pftCreationTime;
		FILETIME pftExitTime;
		FILETIME pftKernelTime;
		FILETIME pftUserTime;

		if (GetProcessTimes(ProcHandle[lParam], &pftCreationTime, &pftExitTime, &pftKernelTime, &pftUserTime))
		{
			
			SYSTEMTIME sysCreationTime;
			SYSTEMTIME sysExitTime;

			FileTimeToSystemTime(&pftCreationTime, &sysCreationTime);
			FileTimeToSystemTime(&pftExitTime, &sysExitTime);

			//вермя жизни процесса
			ULONG onTime;
			onTime = pftExitTime.dwLowDateTime - pftCreationTime.dwLowDateTime;
			wsprintf(Buf, TEXT("%d"), onTime / 10000);
			SetDlgItemText(hDlg, IDC_EDIT9, Buf);

            //время выполнения в режиме пользователя
			wsprintf(Buf, TEXT("%d"), pftUserTime);
			SetDlgItemText(hDlg, IDC_EDIT10, Buf);

             //время выполнени в режиме ядра
			wsprintf(Buf, TEXT("%d"), pftKernelTime);
			SetDlgItemText(hDlg, IDC_EDIT11, Buf);

			//время простоя процесса
			ULONG workTime = pftKernelTime.dwLowDateTime + pftUserTime.dwLowDateTime;
			ULONG sleepTime = onTime - workTime;
			wsprintf(Buf, TEXT("%d"), sleepTime / 10000);
			SetDlgItemText(hDlg, IDC_EDIT12, Buf);

		}
		///////////////////////////////

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


void OpenFileDialog(HWND hWnd)
{
	OPENFILENAME ofn;   // структура для common dialog box
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;  
	ofn.lpstrFile = FileName;
	ofn.lpstrFile[0] = TEXT('\0');
	ofn.nMaxFile = sizeof(FileName);
	
	ofn.lpstrFilter = TEXT("All\0*.*\0Text\0*.TXT\0Image\0*.BMP");
	ofn.nFilterIndex = 1; // Индекс для текущего шаблона фильтра
	ofn.lpstrFileTitle = NULL; // Без заголовка
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL; // В качестве начального текущий каталог
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Отображение диалогового окна
	BOOL fRet = GetOpenFileName(&ofn);
}