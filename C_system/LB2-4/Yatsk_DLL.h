// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the YATSK_DLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// YATSK_DLL_API functions as being imported from a DLL, whereas this DLL sees symbols

// defined with this macro as being exported.
#include <stdio.h>

#ifdef YATSK_DLL_EXPORTS
#define YATSK_DLL_API __declspec(dllexport)
#else
#define YATSK_DLL_API __declspec(dllimport)
#endif

extern YATSK_DLL_API int g_nDllCallsCount;  //счетчик загрузок библиотеки, переменная разделяемая между процессами
extern YATSK_DLL_API int g_nFnCallsCount;  //счетчик вызова функций библиотеки в отд процессе, увелич-ся клиент, польз программой

YATSK_DLL_API int Fun121(double, double);
YATSK_DLL_API float Fun122(int, int, int);
YATSK_DLL_API void Fun123(int in, int *out);

// This class is exported from the Yatsk_DLL.dll
class YATSK_DLL_API CYatsk_DLL 
{
public:
	CYatsk_DLL(void);
	// TODO: add your methods here.
};
//
//extern YATSK_DLL_API int nYatsk_DLL;
//
//YATSK_DLL_API int fnYatsk_DLL(void);

 // Протитипы функций для СР
YATSK_DLL_API FILE* WINAPI FnSR1();

YATSK_DLL_API void WINAPI FnSR4(FILE*, int*, char[]);
YATSK_DLL_API void WINAPI FnSR5(int);

