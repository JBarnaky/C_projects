//
// СFN_15.cpp
//
 
#include <windows.h>
#include "CFN_15.h"

//
// Math class implementation
//
// Constructors
CFN_15::CFN_15()
{
   m_lRef = 0;
 
   // Увеличить значение внешнего счетчика объектов
   InterlockedIncrement( &g_lObjs_ind ); 
}
 
// The destructor
CFN_15::~CFN_15()
{
   // Уменьшить значение внешнего счетчика объектов
   InterlockedDecrement( &g_lObjs_ind ); 
}

STDMETHODIMP CFN_15::QueryInterface( REFIID riid, void** ppv )
{
    *ppv = 0;
 
    if ( riid == IID_IUnknown || riid== IID_IFN_15 )
		*ppv = (IFN_15*) this;
	else if(riid==IID_IVer)
		*ppv = (IVer*) this;
 
    if ( *ppv )
    {
        AddRef();
        return( S_OK );
    }
    return (E_NOINTERFACE);
}
 
STDMETHODIMP_(ULONG) CFN_15::AddRef()
{
   return InterlockedIncrement( &m_lRef );
}
 
STDMETHODIMP_(ULONG) CFN_15::Release()
{
   if ( InterlockedDecrement( &m_lRef ) == 0 )
   {
      delete this;
      return 0;
   }
 
   return m_lRef;
}

STDMETHODIMP CFN_15::Fun151( int lOp1, int lOp2, float* pResult )
{
   *pResult = lOp1 + lOp2;
   return S_OK;
}
 
STDMETHODIMP CFN_15::Fun152( int lOp1, int lOp2, int lOp3, float* pResult )
{
   *pResult = (float)lOp1 - lOp2 - lOp3;
   return S_OK;
}
 
STDMETHODIMP CFN_15::Fun153( double lOp1, double* pResult )
{
   *pResult = lOp1 * lOp1;
   return S_OK;
}
STDMETHODIMP CFN_15::GetAuthor(wchar_t** pResult)
{
	/**pResult=TEXT("Paul Yatskevich 70322");
	return S_OK;*/
	
	wchar_t* name=L"PAUL YATSKEVICH 70322";
	wchar_t* p =(wchar_t*)CoTaskMemAlloc(wcslen(name));

	wcscpy(p,name);
	*pResult=p;
	return S_OK;
}



FN_15ClassFactory::FN_15ClassFactory()
{
   m_lRef = 0;
}
 
FN_15ClassFactory::~FN_15ClassFactory()
{
}
 
STDMETHODIMP FN_15ClassFactory::QueryInterface( REFIID riid, void** ppv )
{
   *ppv = 0;
 
   if ( riid == IID_IUnknown || riid == IID_IClassFactory )
      *ppv = this;
 
   if ( *ppv )
   {
      AddRef();
      return S_OK;
   }
 
   return(E_NOINTERFACE);
}
 
STDMETHODIMP_(ULONG) FN_15ClassFactory::AddRef()
{
   return InterlockedIncrement( &m_lRef );
}
 
STDMETHODIMP_(ULONG) FN_15ClassFactory::Release()
{
   if ( InterlockedDecrement( &m_lRef ) == 0 )
   {
      delete this;
      return 0;
   }
 
   return m_lRef;
}
 
STDMETHODIMP FN_15ClassFactory::CreateInstance
     ( LPUNKNOWN pUnkOuter, REFIID riid, void** ppvObj )
{
   CFN_15*      pCFN_15;
   HRESULT    hr;
 
   *ppvObj = 0;
 
   pCFN_15 = new CFN_15;
 
   if ( pCFN_15 == 0 )
      return( E_OUTOFMEMORY );
 
   hr = pCFN_15->QueryInterface( riid, ppvObj );
 
   if ( FAILED( hr ) )
      delete pCFN_15;
 
   return hr;
}
 
STDMETHODIMP FN_15ClassFactory::LockServer( BOOL fLock )
{
   if ( fLock )
      InterlockedIncrement( &g_lLocks_ind ); 
   else
      InterlockedDecrement( &g_lLocks_ind );
 
    return S_OK;
}