#include <Windows.h>
#include "CFN_15.h"

//Constructors
CFN_15::CFN_15()
{
	m_lRef=0;

	//increment objects count(out)

	InterlockedIncrement(&g_lObjs);
}
	//Destructors

CFN_15::~CFN_15()
{
	//decrement objects count(out)

	InterlockedDecrement(&g_lObjs);
}

STDMETHODIMP CFN_15::QueryInterface(REFIID riid, void** pvv)
{
	/**pvv=0;

	if(riid==IID_IUnknown || riid==IID_IFN_15)
		*pvv=this;
	if(riid==IID_IUnknown || riid==IID_IVer)
		*pvv=this;
	if(*pvv)
	{
		AddRef();
		return(S_OK);
	}
	return(E_NOINTERFACE);*/


	*pvv=0;
	if(riid==IID_IUnknown)
	{
		*pvv=(IFN_15*)(this);
	}
	else if (riid==IID_IFN_15)
	{
		*pvv=(IFN_15*)(this);
	}
	else if(riid==IID_IVer)
	{
		*pvv=(Iver*)(this);
	}
	else
	{
		*pvv=NULL;
		return E_NOINTERFACE;
	}
	if(*pvv)
	{
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;

}

STDMETHODIMP_(ULONG) CFN_15::AddRef()
{
	return InterlockedIncrement(&m_lRef);
}

STDMETHODIMP_(ULONG) CFN_15::Release()
{
	if(InterlockedDecrement(&m_lRef)==0)
	{
		delete this;
		return 0;
	}
	return m_lRef;
}

STDMETHODIMP CFN_15::Fun151(int lOp1, int lOp2, float* pResult)
{
	*pResult=lOp1+lOp2;
	return S_OK;
}

STDMETHODIMP CFN_15::Fun152(int lOp1, int lOp2, int lOp3, float* pResult)
{
	*pResult=lOp1-lOp2-lOp3;
	return S_OK;
}

STDMETHODIMP CFN_15::Fun153(double lOp1, double* pResult)
{
	*pResult=lOp1*lOp1;
	return S_OK;
}

STDMETHODIMP CFN_15::GetAuthor(wchar_t** pResult)
{
	*pResult=TEXT("Yatskevich 70322");
	return S_OK;
}


IFN15_ClassFactory::IFN15_ClassFactory()
{
	m_lRef=0;
}

IFN15_ClassFactory::~IFN15_ClassFactory()
{

}

STDMETHODIMP IFN15_ClassFactory::QueryInterface(REFIID riid, void** pvv)
{
	*pvv=0;
	if(riid==IID_IUnknown || riid==IID_IClassFactory)
		*pvv=this;
	if(*pvv)
	{
		AddRef();
		return S_OK;
	}
	return (E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) IFN15_ClassFactory::AddRef()
{
	return InterlockedIncrement(&m_lRef);
}

STDMETHODIMP_(ULONG) IFN15_ClassFactory::Release()
{
	if(InterlockedDecrement(&m_lRef)==0)
	{
		delete this;
		return 0;
	}
	return m_lRef;
}

STDMETHODIMP IFN15_ClassFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void** ppvObj)
{
	CFN_15* pCFN_15;
	HRESULT hr;

	*ppvObj=0;
	pCFN_15=new CFN_15;

	if(pCFN_15==0)
		return(E_NOINTERFACE);
	hr=pCFN_15->QueryInterface(riid, ppvObj);
	if(FAILED(hr))
		delete pCFN_15;
	return hr;
}

STDMETHODIMP IFN15_ClassFactory::LockServer(BOOL flock)
{
	if(flock)
		InterlockedIncrement(&g_lLocks);
	else
		InterlockedDecrement(&g_lLocks);

	return S_OK;
}
