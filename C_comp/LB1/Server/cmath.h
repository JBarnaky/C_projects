//
//CMath.h
//
#include "imath.h"

extern long g_lObjs;
extern long g_lLocks;

//описание класса
class CMath: public IMath
{
protected:
	//счетчик ссылок
	long m_lRef;

public:
	CMath();
	~CMath();

public: //описание IUnknown
	STDMETHOD(QueryInterface(REFIID, void**));
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());

	//IMath
	STDMETHOD(Add(long, long, long*));
	STDMETHOD(Subtract(long, long, long*));
	STDMETHOD(Multiply(long, long, long*));
	STDMETHOD(Divide(long, long, long*));
};

class MathClassFactory : public IClassFactory
{
protected:
	long m_lRef;

public:
	MathClassFactory();
	~MathClassFactory();

	//IUnknown
	STDMETHOD(QueryInterface(REFIID, void**));
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());

	//IClassFactory
	STDMETHOD(CreateInstance(LPUNKNOWN, REFIID, void**));
	STDMETHOD(LockServer(BOOL));

};