//
// CFN_15.h
//
#include <windows.h> 
#include "IFN_15.h"

 
extern long g_lObjs_ind;
extern long g_lLocks_ind;
 
 
class CFN_15 : public IFN_15, public IVer
{
protected:
   // Reference count
   long          m_lRef;
 
public:
   CFN_15();
   ~CFN_15();
 
public:
   // IUnknown
   STDMETHOD(QueryInterface( REFIID, void** ));
   STDMETHOD_(ULONG, AddRef());
   STDMETHOD_(ULONG, Release());
 
   // IFN_15
   STDMETHOD(Fun151(int, int, float*));
   STDMETHOD(Fun152 (int, int, int, float*));
   STDMETHOD(Fun153 (double, double* ));

      // IVer
 STDMETHOD(GetAuthor(wchar_t**));
};
 
class FN_15ClassFactory : public IClassFactory
{
protected:
   long       m_lRef;
 
public:
   FN_15ClassFactory();
   ~FN_15ClassFactory();
 
   // IUnknown
   STDMETHOD( QueryInterface(REFIID, void** ));
   STDMETHOD_(ULONG, AddRef());
   STDMETHOD_(ULONG, Release());
 
   // IClassFactory
   STDMETHOD( CreateInstance(LPUNKNOWN, REFIID, void**));
   STDMETHOD( LockServer(BOOL));
};