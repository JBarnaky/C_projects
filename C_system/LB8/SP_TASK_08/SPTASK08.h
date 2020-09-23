// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SPTASK08_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SPTASK08_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SPTASK08_EXPORTS
#define SPTASK08_API __declspec(dllexport)
#else
#define SPTASK08_API __declspec(dllimport)
#endif

// This class is exported from the SPTASK08.dll
class SPTASK08_API CSPTASK08 {
public:
	CSPTASK08(void);
	// TODO: add your methods here.
};

extern SPTASK08_API int nSPTASK08;
extern SPTASK08_API int g_nDllFlag;
extern SPTASK08_API int g_x;
extern SPTASK08_API int g_y;

SPTASK08_API int fnSPTASK08(void);
SPTASK08_API int add(void);
SPTASK08_API int sub(void);
SPTASK08_API int mult(void);
SPTASK08_API int div(void);
