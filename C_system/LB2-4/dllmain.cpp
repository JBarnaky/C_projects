// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Yatsk_DLL.h"

TCHAR filename[260];
TCHAR buf[200];

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		
	case DLL_PROCESS_ATTACH:
		
		DWORD mod;
		mod= GetModuleFileName(hModule, filename, 260);  //�������� ��� ������
		wsprintf(buf, TEXT("����������� ���������� %s. ������ �������� �.�."), filename);
		MessageBox(NULL, buf, TEXT("DLLMain"), MB_OK);

		g_nDllCallsCount++;
		return TRUE;
		break;

	case DLL_THREAD_ATTACH:
		MessageBox(NULL, TEXT("������ ����� �����"), TEXT("DLLMain"), MB_OK);
		break;

	case DLL_THREAD_DETACH:
		MessageBox(NULL, TEXT("���������� �����"), TEXT("DLLMain"), MB_OK);
		break;

	case DLL_PROCESS_DETACH:
		wsprintf(buf, TEXT("����������� ���������� %s. ������ �������� �.�."), filename);
		MessageBox(NULL, buf, TEXT("DLLMain"), MB_OK);
		break;

	}
	return TRUE;
}

