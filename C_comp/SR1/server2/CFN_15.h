#include "IFN_15.h"

extern long g_lObjs;
extern long g_lLocks;

//описание класса
class CFN_15: public IFN_15, public Iver
{
protected:
	//счетчик ссылок
	long m_lRef;

public:
	CFN_15();
	~CFN_15();

public: //описание IUnknown
	STDMETHOD(QueryInterface(REFIID, void**));
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());

	//IFN_15
	STDMETHOD(Fun151(int, int, float*));
	STDMETHOD(Fun152(int, int, int, float*));
	STDMETHOD(Fun153(double, double*));

	//IVer
	STDMETHOD(GetAuthor(wchar_t**));
};

class IFN15_ClassFactory : public IClassFactory
{
protected:
	long m_lRef;

public:
	IFN15_ClassFactory();
	~IFN15_ClassFactory();

	//IUnknown
	STDMETHOD(QueryInterface(REFIID, void**));
	STDMETHOD_(ULONG, AddRef());
	STDMETHOD_(ULONG, Release());

	//IClassFactory
	STDMETHOD(CreateInstance(LPUNKNOWN, REFIID, void**));
	STDMETHOD(LockServer(BOOL));

};

