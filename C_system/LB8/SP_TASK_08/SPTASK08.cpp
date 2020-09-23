// SPTASK08.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SPTASK08.h"

// указывает компилятору поместить эту инициализированную переменную 
// в раздел Shared, чтобы она стала доступной всем экземплярам программы. 
#pragma data_seg("Shared")
__declspec(dllexport) int g_nDllFlag = 0; // Флаг для установки значений
__declspec(dllexport) int g_x = 0; // Переменная X
__declspec(dllexport) int g_y = 0; // Переменная Y
#pragma data_seg() // указываем компоновщику, что раздел Shared должен быть читаемым, записываемым и разделяемым. 
#pragma comment(linker, "/Section:Shared,RWS") 

// This is an example of an exported variable
SPTASK08_API int nSPTASK08=0;
__declspec(dllexport) int add(); // Функция возвращает сумму
__declspec(dllexport) int sub(); // Функция возвращает разность
__declspec(dllexport) int mult(); // Функция возвращает произведение
__declspec(dllexport) int div(); // Функция возвращает частное

// This is an example of an exported function.
SPTASK08_API int fnSPTASK08(void)
{
    return 42;
}

int add()
{
	return g_x + g_y;
}

int sub()
{
	return g_x - g_y;
}

int mult()
{
	return g_x * g_y;
}

int div()
{
	return g_y==0 ? 0 : g_x / g_y;
}

// This is the constructor of a class that has been exported.
// see SPTASK08.h for the class definition
CSPTASK08::CSPTASK08()
{
    return;
}
