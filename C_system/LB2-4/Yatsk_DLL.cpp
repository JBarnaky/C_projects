// Yatsk_DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Yatsk_DLL.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <process.h>   
#include <locale.h>     
#include <string.h>
#include <ctype.h>



//// This is an example of an exported variable
//YATSK_DLL_API int nYatsk_DLL=0;  //24
//
//// This is an example of an exported function.
//YATSK_DLL_API int fnYatsk_DLL(void)
//{
//	return 42;    //49
//}

YATSK_DLL_API int g_nFnCallsCount = 0;

#pragma data_seg (".ASHARE")
YATSK_DLL_API int g_nDllCallsCount;  //счетчик загрузок библиотеки, переменная разделяемая между процессами
#pragma data_seg()

#pragma comment (linker, "/SECTION:.ASHARE,RWS")



YATSK_DLL_API int Fun121(double x, double y)
{
	return (int)(x + y);
}
YATSK_DLL_API float Fun122(int x, int y, int z)
{
	return (float)(x + y)*z;
}
YATSK_DLL_API void Fun123(int x, int *y)
{
	*y += x;
}



// This is the constructor of a class that has been exported.
// see Yatsk_DLL.h for the class definition
CYatsk_DLL::CYatsk_DLL()
{
	return;
}


// Реализация функций СР
// 1. Открытие и создание копии файла
FILE* WINAPI FnSR1()
{
	FILE* fileExist;
	fopen_s(&fileExist, "test.txt", "r");
	if (fileExist == NULL)
	{
		MessageBox(NULL, TEXT("Файл не существует"), TEXT("Yatsk_DLL"), MB_OK);
	}
	else
	{
		CopyFile(TEXT("test.txt"), TEXT("temp.txt"), FALSE);
	}
	return fileExist;
}


// 4. Получение колиества слов с гласной
void WINAPI FnSR4(FILE* file, int *wordCount, char buff[1000])
{
	int j = 0, k = 0;
	BOOL wordFlag = FALSE;
	char ch;
	char glasn[] = "уеыаоэяиюУЕЫАОЭЯИЮ";
	if (file != NULL)
	{
		fgets(buff, 1000, file);
		for (int i = 0; i < strlen(buff); i++)
		{
			ch = buff[i];
			for (int l = 0; l <= strlen(glasn); l++)
			{
				if (buff[i] == glasn[l] && buff[i - 1] == ' ')
				{
					*wordCount = *wordCount + 1;
				}
				if (buff[i] == glasn[l] && i == 0)
				{
					*wordCount = *wordCount + 1;
				}
			}
		}
	}
	else
	{
		MessageBox(NULL, TEXT("Файл не существует"), TEXT("Yatsk_DLL"), MB_OK);
	}
	fclose(file);
}

// 5. Добавление информации в файл
void WINAPI FnSR5(int wordCount)
{
	char addStr[40] = "";
	FILE* fileExist;
	fopen_s(&fileExist, "temp.txt", "a+");
	if (fileExist == NULL)
	{
		MessageBox(NULL, TEXT("Файл не существует"), TEXT("Yatsk_DLL"), MB_OK);
	}
	else
	{
		sprintf_s(addStr, "\nКоличество слов начинающихся с гласных = %d", wordCount, 40);
		fwrite(&addStr, sizeof(char), strlen(addStr), fileExist);
	}
	fclose(fileExist);
}
