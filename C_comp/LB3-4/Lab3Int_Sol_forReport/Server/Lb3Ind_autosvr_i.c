

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Nov 08 21:55:53 2017
 */
/* Compiler settings for Lb3Ind_autosvr.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IMyInd,0xAF644FB0,0x7E6A,0x456E,0xA9,0x54,0x6D,0xB9,0xD5,0x04,0x54,0xC5);


MIDL_DEFINE_GUID(IID, IID_IMyInd_Author,0x2715B9FA,0x42DF,0x4B28,0x97,0x70,0xF9,0x07,0x06,0x9F,0xC2,0x4E);


MIDL_DEFINE_GUID(IID, LIBID_Lb3Ind_autosvrLib,0x9841AA19,0x0E11,0x4C63,0x95,0x8B,0xEC,0xBC,0xB7,0xA4,0xF9,0xFB);


MIDL_DEFINE_GUID(CLSID, CLSID_CoMyInd,0x7A1B878B,0x1CE4,0x41EB,0x9D,0xC4,0xD3,0x51,0xA0,0xD8,0x6C,0xE9);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



