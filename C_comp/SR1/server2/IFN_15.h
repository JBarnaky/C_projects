//IFN_15
#include<windows.h>

// {9BAA9BFF-E46F-4277-8828-6D6B3CC384D7}
DEFINE_GUID(CLSID_CFN_15, 
0x9baa9bff, 0xe46f, 0x4277, 0x88, 0x28, 0x6d, 0x6b, 0x3c, 0xc3, 0x84, 0xd7);

// {5DCE503A-E8C3-45CF-B43F-4DCEC109247D}
DEFINE_GUID(IID_IFN_15, 
0x5dce503a, 0xe8c3, 0x45cf, 0xb4, 0x3f, 0x4d, 0xce, 0xc1, 0x9, 0x24, 0x7d);

// {8E76C97D-8E26-40F5-BBB3-22D40E2AF18F}
DEFINE_GUID(IID_IVer, 
0x8e76c97d, 0x8e26, 0x40f5, 0xbb, 0xb3, 0x22, 0xd4, 0xe, 0x2a, 0xf1, 0x8f);

//описание интерфейса
class IFN_15 : public IUnknown
{
public:
	STDMETHOD(Fun151(int, int, float*)) PURE;
	STDMETHOD(Fun152(int, int, int, float*)) PURE;
	STDMETHOD(Fun153(double, double*)) PURE;
};

class Iver : public IUnknown
{
public:
	STDMETHOD(GetAuthor(wchar_t ** author)) PURE;
};
