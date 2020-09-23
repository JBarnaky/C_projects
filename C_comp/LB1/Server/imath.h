//
//IMath.h
//
#include<windows.h>

// {5DCE503A-E8C3-45CF-B43F-4DCEC109247D}
DEFINE_GUID(IID_IMath, 
0x5dce503a, 0xe8c3, 0x45cf, 0xb4, 0x3f, 0x4d, 0xce, 0xc1, 0x9, 0x24, 0x7d);

// {9BAA9BFF-E46F-4277-8828-6D6B3CC384D7}
DEFINE_GUID(CLSID_CMath, 
0x9baa9bff, 0xe46f, 0x4277, 0x88, 0x28, 0x6d, 0x6b, 0x3c, 0xc3, 0x84, 0xd7);

//описание интерфейса
class IMath : public IUnknown
{
public:
	STDMETHOD(Add(long, long, long*)) PURE;
	STDMETHOD(Subtract(long, long, long*)) PURE;
	STDMETHOD(Multiply(long, long, long*)) PURE;
	STDMETHOD(Divide(long, long, long*)) PURE;
};
