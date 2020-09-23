// MyInd.h : Declaration of the CMyInd

#pragma once
#include "resource.h"       // main symbols



#include "Lb3Ind_autosvr_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CMyInd

class ATL_NO_VTABLE CMyInd :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyInd, &CLSID_CoMyInd>,
	public IDispatchImpl<IMyInd, &IID_IMyInd, &LIBID_Lb3Ind_autosvrLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<IMyInd_Author, &IID_IMyInd_Author, &LIBID_Lb3Ind_autosvrLib, 1, 0>
{
public:
	CMyInd()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MYIND)


BEGIN_COM_MAP(CMyInd)
	COM_INTERFACE_ENTRY(IMyInd)
	COM_INTERFACE_ENTRY(IMyInd_Author)
	COM_INTERFACE_ENTRY2(IDispatch, IMyInd)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(Fun71)(LONG x, LONG y, DOUBLE* z);
	STDMETHOD(Fun72)(LONG x, LONG y, LONG n, DOUBLE* z);
	STDMETHOD(Fun73)(DOUBLE x, DOUBLE* y);
	STDMETHOD(GetAuthor(wchar_t ** author));
};

OBJECT_ENTRY_AUTO(__uuidof(CoMyInd), CMyInd)
