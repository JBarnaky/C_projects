//
// ifn_15.h
//
 #include <windows.h>


// {A84CF95D-5EF7-49C9-BEB3-6854371011B1}
DEFINE_GUID(CLSID_FN_15, 
0xa84cf95d, 0x5ef7, 0x49c9, 0xbe, 0xb3, 0x68, 0x54, 0x37, 0x10, 0x11, 0xb1);

// {FA971293-1ECD-4BDA-A458-5FBEE86641BF}
DEFINE_GUID(IID_IFN_15, 
0xfa971293, 0x1ecd, 0x4bda, 0xa4, 0x58, 0x5f, 0xbe, 0xe8, 0x66, 0x41, 0xbf);

// {3A944C30-ED91-4F1F-8045-D76D6708547E}
DEFINE_GUID(IID_IVer, 
0x3a944c30, 0xed91, 0x4f1f, 0x80, 0x45, 0xd7, 0x6d, 0x67, 0x8, 0x54, 0x7e);


class IFN_15 : public IUnknown
{
public:
   STDMETHOD(Fun151(int, int, float*)) PURE;
   STDMETHOD(Fun152 (int, int, int, float*)) PURE;
   STDMETHOD(Fun153 (double, double* )) PURE;
};

class IVer : public IUnknown
{
public:
	STDMETHOD(GetAuthor(wchar_t ** author)) PURE;
};
