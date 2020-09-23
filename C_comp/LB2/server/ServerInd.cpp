//
// server.cpp : Defines the initialization routines for the DLL.
//
 
#include <windows.h>
 
#include <initguid.h>
#include "CFN_15.h"

#include "Registry.h"   // Registry helper functions
 
static HMODULE g_hModule = NULL ;   // DLL module handle
long    g_lObjs_ind = 0;
long    g_lLocks_ind = 0;

// Friendly name of component
const char g_szFriendlyName[] = "TKP_Lab1_YatskCOM" ;

// Version-independent ProgID
const char g_szVerIndProgID[] = "YatskCOM" ;

// ProgID
const char g_szProgID[] = "YatskCOM.1" ;
 
STDAPI DllGetClassObject( REFCLSID rclsid, REFIID riid, void** ppv )
{
   HRESULT             hr;
   FN_15ClassFactory    *pCF;
 
   pCF = 0;
 
   // Make sure the CLSID is for our Expression component
   if ( rclsid != CLSID_FN_15 )
      return( E_FAIL );
 
   pCF = new FN_15ClassFactory;
 
   if ( pCF == 0 )
      return( E_OUTOFMEMORY );
 
   hr = pCF->QueryInterface( riid, ppv );
 
   // Check for failure of QueryInterface
   if ( FAILED( hr ) )
   {
      delete pCF;
      pCF = 0;
   }
 
   return hr;
}
 
STDAPI DllCanUnloadNow(void)
{
    if ( g_lObjs_ind || g_lLocks_ind )
       return( S_FALSE );
    else
       return( S_OK );
}

//
// Server registration
//
STDAPI DllRegisterServer()
{
	return RegisterServer(g_hModule, 
	                      CLSID_FN_15,
	                      g_szFriendlyName,
	                      g_szVerIndProgID,
	                      g_szProgID) ;
}


//
// Server unregistration
//
STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_FN_15,
	                        g_szVerIndProgID,
	                        g_szProgID) ;
}

///////////////////////////////////////////////////////////
//
// DLL module information
//
BOOL APIENTRY DllMain(HANDLE hModule,
                      DWORD dwReason,
                      void* lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_hModule = (HMODULE)hModule ;
	}
	return TRUE ;
}