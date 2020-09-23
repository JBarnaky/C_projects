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
		mod= GetModuleFileName(hModule, filename, 260);  //получить имя модуля
		wsprintf(buf, TEXT("Загружается библиотека %s. Проект Яцкевича П.К."), filename);
		MessageBox(NULL, buf, TEXT("DLLMain"), MB_OK);

		g_nDllCallsCount++;
		return TRUE;
		break;

	case DLL_THREAD_ATTACH:
		MessageBox(NULL, TEXT("Создан новый поток"), TEXT("DLLMain"), MB_OK);
		break;

	case DLL_THREAD_DETACH:
		MessageBox(NULL, TEXT("Завершился поток"), TEXT("DLLMain"), MB_OK);
		break;

	case DLL_PROCESS_DETACH:
		wsprintf(buf, TEXT("Выгружается библиотека %s. Проект Яцкевича П.К."), filename);
		MessageBox(NULL, buf, TEXT("DLLMain"), MB_OK);
		break;

	}
	return TRUE;
}

