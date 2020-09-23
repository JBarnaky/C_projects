// MyMath.h : Declaration of the CMyMath

#pragma once
#include "resource.h"       // main symbols



#include "Lb3_autosvr_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CMyMath

class ATL_NO_VTABLE CMyMath :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyMath, &CLSID_CoMyMath>,
	public IDispatchImpl<IMyMath, &IID_IMyMath, &LIBID_Lb3_autosvrLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMyMath()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MYMATH)


BEGIN_COM_MAP(CMyMath)
	COM_INTERFACE_ENTRY(IMyMath)
	COM_INTERFACE_ENTRY(IDispatch)
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



	STDMETHOD(Add)(LONG x, LONG y, LONG* z);
	STDMETHOD(Subtract)(LONG x, LONG y, LONG* z);
	STDMETHOD(Multiply)(LONG x, LONG y, LONG* z);
	STDMETHOD(Divide)(LONG x, LONG y, LONG* z);
};

OBJECT_ENTRY_AUTO(__uuidof(CoMyMath), CMyMath)
