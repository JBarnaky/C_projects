#include <Windows.h>
#include <InitGuid.h>
#include "CFN_15.h"

long g_lObjs=0;
long g_lLocks=0;

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	HRESULT hr;
	IFN15_ClassFactory *pCF;
	pCF=0;

	if(rclsid != CLSID_CFN_15)
		return(E_FAIL);
	pCF = new IFN15_ClassFactory;
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
