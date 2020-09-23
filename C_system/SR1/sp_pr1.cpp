#include <Windows.h>
#include "sp_pr1.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	TCHAR buf1[300] = TEXT("");

	TCHAR buf[500] = TEXT("");

	LPCTSTR lpszHelloText1 = MESSAGE_TEXT;
	LPCTSTR lpszHelloText2 = TEXT("�����<�������, 60322-1>\n");
	LPCTSTR lpszHelloText3 = TEXT("Design time=<21/10/2017 21:34:12>\n");
	wsprintf(buf1, TEXT("Run time=����-%d, �����-%d, ���-%d, �����-%d:%d:%d"), st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);

	LPCTSTR lpszHelloWndTitle = MESSAGE_TITLE;


	lstrcat(buf, lpszHelloText1);
	lstrcat(buf, lpszHelloText2);
	lstrcat(buf, lpszHelloText3);
	lstrcat(buf, buf1);

	
	MessageBox(NULL, buf, lpszHelloWndTitle, MB_OK);
	
	
	int iRetValue1, iRetValue2;
	LPCTSTR lpszMesBoxTitle = TEXT("������� 12");
	LPTSTR lpszResponce;
	do{
		iRetValue1 = MessageBox(NULL, TEXT("������� ���� �� ������."), lpszMesBoxTitle,
			MB_ABORTRETRYIGNORE | MB_ICONSTOP | MB_SETFOREGROUND | MB_DEFBUTTON3);

		switch (iRetValue1)
		{
		case IDABORT:
			lpszResponce = TEXT("������ ������ �������� (ABORT)");
			break;
		case IDRETRY:
			lpszResponce = TEXT("������ ������ ��������� (RETRY)");
			break;
		case IDIGNORE:
			lpszResponce = TEXT("������ ������ ���������� (IGNORE)");
			break;
		default: lpszResponce = TEXT("����� ��� �� �������.");
		}
		TCHAR buf[200] = TEXT("");
		lstrcat(buf, lpszResponce);
		lstrcat(buf, TEXT(" ���������� �������� ������������ ��������?"));
		iRetValue2 = MessageBox(NULL, buf, lpszMesBoxTitle,
			MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);
	} while (iRetValue2 != IDNO);

	return 0;
}
