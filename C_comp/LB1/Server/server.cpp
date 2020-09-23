//
//server.cpp : Defines the initialization routines for the DLL
//

#include <Windows.h>
#include <InitGuid.h>
#include "cmath.h"

long g_lObjs=0;
long g_lLocks=0;

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	HRESULT hr;
	MathClassFactory *pCF;
	pCF=0;

	if(rclsid != CLSID_CMath)
		return(E_FAIL);
	pCF = new MathClassFactory;
	if(pCF==0)
		return(E_OUTOFMEMORY);
	hr=pCF->QueryInterface(riid, ppv);
	if(FAILED(hr))
	{
		delete pCF;
		pCF=0;
	}
	return hr;
}

STDAPI DllCanUnloadNow(void)
{
	if(g_lObjs || g_lLocks)
		return(S_FALSE);
	else
		return(S_OK);
}