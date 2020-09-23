

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Lb3Ind_autosvr_i_h__
#define __Lb3Ind_autosvr_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyInd_FWD_DEFINED__
#define __IMyInd_FWD_DEFINED__
typedef interface IMyInd IMyInd;
#endif 	/* __IMyInd_FWD_DEFINED__ */


#ifndef __IMyInd_Author_FWD_DEFINED__
#define __IMyInd_Author_FWD_DEFINED__
typedef interface IMyInd_Author IMyInd_Author;
#endif 	/* __IMyInd_Author_FWD_DEFINED__ */


#ifndef __CoMyInd_FWD_DEFINED__
#define __CoMyInd_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoMyInd CoMyInd;
#else
typedef struct CoMyInd CoMyInd;
#endif /* __cplusplus */

#endif 	/* __CoMyInd_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IMyInd_INTERFACE_DEFINED__
#define __IMyInd_INTERFACE_DEFINED__

/* interface IMyInd */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyInd;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF644FB0-7E6A-456E-A954-6DB9D50454C5")
    IMyInd : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Fun151( 
            /* [in] */ LONG x,
            /* [in] */ LONG y,
            /* [retval][out] */ DOUBLE *z) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Fun152( 
            /* [in] */ LONG x,
            /* [in] */ LONG y,
			/* [in] */ LONG n,
            /* [retval][out] */ DOUBLE *z) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Fun153( 
            /* [in] */ DOUBLE x,
            /* [retval][out] */ DOUBLE *y) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyIndVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyInd * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyInd * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyInd * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyInd * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyInd * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyInd * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyInd * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Fun71 )( 
            IMyInd * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y,
            /* [retval][out] */ LONG *z);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Fun72 )( 
            IMyInd * This,
            /* [in] */ LONG x,
            /* [in] */ LONG y,
            /* [retval][out] */ DOUBLE *z);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Fun73 )( 
            IMyInd * This,
            /* [in] */ DOUBLE x,
            /* [retval][out] */ DOUBLE *y);
        
        END_INTERFACE
    } IMyIndVtbl;

    interface IMyInd
    {
        CONST_VTBL struct IMyIndVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyInd_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyInd_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyInd_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyInd_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyInd_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyInd_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyInd_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMyInd_Fun151(This,x,y,z)	\
    ( (This)->lpVtbl -> Fun151(This,x,y,z) ) 

#define IMyInd_Fun152(This,x,y,z)	\
    ( (This)->lpVtbl -> Fun152(This,x,y,n,z) ) 

#define IMyInd_Fun153(This,x,y)	\
    ( (This)->lpVtbl -> Fun153(This,x,y) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyInd_INTERFACE_DEFINED__ */


#ifndef __IMyInd_Author_INTERFACE_DEFINED__
#define __IMyInd_Author_INTERFACE_DEFINED__

/* interface IMyInd_Author */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyInd_Author;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2715B9FA-42DF-4B28-9770-F907069FC24E")
    IMyInd_Author : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAuthor( 
            /* [in] */ wchar_t **author) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyInd_AuthorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyInd_Author * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyInd_Author * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyInd_Author * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyInd_Author * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyInd_Author * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyInd_Author * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyInd_Author * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAuthor )( 
            IMyInd_Author * This,
            /* [in] */ wchar_t **author);
        
        END_INTERFACE
    } IMyInd_AuthorVtbl;

    interface IMyInd_Author
    {
        CONST_VTBL struct IMyInd_AuthorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyInd_Author_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyInd_Author_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyInd_Author_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyInd_Author_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyInd_Author_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyInd_Author_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyInd_Author_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMyInd_Author_GetAuthor(This,author)	\
    ( (This)->lpVtbl -> GetAuthor(This,author) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyInd_Author_INTERFACE_DEFINED__ */



#ifndef __Lb3Ind_autosvrLib_LIBRARY_DEFINED__
#define __Lb3Ind_autosvrLib_LIBRARY_DEFINED__

/* library Lb3Ind_autosvrLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Lb3Ind_autosvrLib;

EXTERN_C const CLSID CLSID_CoMyInd;

#ifdef __cplusplus

class DECLSPEC_UUID("7A1B878B-1CE4-41EB-9DC4-D351A0D86CE9")
CoMyInd;
#endif
#endif /* __Lb3Ind_autosvrLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


