// SPTASK08.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SPTASK08.h"

// ��������� ����������� ��������� ��� ������������������ ���������� 
// � ������ Shared, ����� ��� ����� ��������� ���� ����������� ���������. 
#pragma data_seg("Shared")
__declspec(dllexport) int g_nDllFlag = 0; // ���� ��� ��������� ��������
__declspec(dllexport) int g_x = 0; // ���������� X
__declspec(dllexport) int g_y = 0; // ���������� Y
#pragma data_seg() // ��������� ������������, ��� ������ Shared ������ ���� ��������, ������������ � �����������. 
#pragma comment(linker, "/Section:Shared,RWS") 

// This is an example of an exported variable
SPTASK08_API int nSPTASK08=0;
__declspec(dllexport) int add(); // ������� ���������� �����
__declspec(dllexport) int sub(); // ������� ���������� ��������
__declspec(dllexport) int mult(); // ������� ���������� ������������
__declspec(dllexport) int div(); // ������� ���������� �������

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
