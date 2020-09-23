#include "targetver.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <tchar.h>

int Rand();

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "RUSSIAN");
	HANDLE hFiles[4] = { 0 };
	int nNumb[4] = { 0 };

	srand((unsigned)time(NULL));
	for (int i = 0; i<4; i++)
	{
		WCHAR Buf[6];
		wsprintf(Buf, L"File%d", i);
		hFiles[i] = CreateFile(Buf, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFiles[i] == INVALID_HANDLE_VALUE)
		{
			puts("Ошибка создания файлов");
			getch();
			return 1;
		}
		nNumb[i] = 1000000 + Rand();//Кол-во чисел в файле
		int* BufOfNumb = (int*)calloc(nNumb[i], sizeof(int));
		if (BufOfNumb == NULL)
		{
			puts("Ошибка. Нехватка памяти");
			getch();
			return 1;
		}
		for (int n = 0; n<nNumb[i]; n++)
		{
			BufOfNumb[n] = rand() % (100 + 1);
		}
		DWORD nWrittenFiles;
		WriteFile(hFiles[i], BufOfNumb, sizeof(int)*nNumb[i], &nWrittenFiles, NULL);
		free(BufOfNumb);

	}
	puts("Файлы созданы успешно");
	getch();
	return 0;
}

int Rand() //случайное число от 1000000 до 2 500 000
{
	int res = 1000000;
	do
	{
		res = rand();
		res = res << 6;
		res += rand();
	} while (res>2500000);
	return res;
}
