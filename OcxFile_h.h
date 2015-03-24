

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Mar 22 17:30:05 2015
 */
/* Compiler settings for OcxFile.odl:
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


#ifndef __OcxFile_h_h__
#define __OcxFile_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DOcxFile_FWD_DEFINED__
#define ___DOcxFile_FWD_DEFINED__
typedef interface _DOcxFile _DOcxFile;
#endif 	/* ___DOcxFile_FWD_DEFINED__ */


#ifndef ___DOcxFileEvents_FWD_DEFINED__
#define ___DOcxFileEvents_FWD_DEFINED__
typedef interface _DOcxFileEvents _DOcxFileEvents;
#endif 	/* ___DOcxFileEvents_FWD_DEFINED__ */


#ifndef __OcxFile_FWD_DEFINED__
#define __OcxFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class OcxFile OcxFile;
#else
typedef struct OcxFile OcxFile;
#endif /* __cplusplus */

#endif 	/* __OcxFile_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __OCXFILELib_LIBRARY_DEFINED__
#define __OCXFILELib_LIBRARY_DEFINED__

/* library OCXFILELib */
/* [control][helpstring][helpfile][version][uuid] */ 


DEFINE_GUID(LIBID_OCXFILELib,0x778A60AE,0xA11E,0x4DE2,0x8E,0x5C,0x13,0xC9,0x6E,0x24,0x3F,0x5B);

#ifndef ___DOcxFile_DISPINTERFACE_DEFINED__
#define ___DOcxFile_DISPINTERFACE_DEFINED__

/* dispinterface _DOcxFile */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DOcxFile,0xB29222EA,0x7DB7,0x4F0A,0xAF,0x18,0x79,0x3F,0xCC,0x0F,0x23,0x09);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B29222EA-7DB7-4F0A-AF18-793FCC0F2309")
    _DOcxFile : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DOcxFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DOcxFile * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DOcxFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DOcxFile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DOcxFile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DOcxFile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DOcxFile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DOcxFile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DOcxFileVtbl;

    interface _DOcxFile
    {
        CONST_VTBL struct _DOcxFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DOcxFile_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DOcxFile_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DOcxFile_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DOcxFile_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DOcxFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DOcxFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DOcxFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DOcxFile_DISPINTERFACE_DEFINED__ */


#ifndef ___DOcxFileEvents_DISPINTERFACE_DEFINED__
#define ___DOcxFileEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DOcxFileEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DOcxFileEvents,0xF0B787D0,0x2D92,0x4FE1,0x9D,0xF3,0xCE,0x7D,0xD3,0x0D,0xF1,0x8F);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F0B787D0-2D92-4FE1-9DF3-CE7DD30DF18F")
    _DOcxFileEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DOcxFileEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DOcxFileEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DOcxFileEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DOcxFileEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DOcxFileEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DOcxFileEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DOcxFileEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DOcxFileEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DOcxFileEventsVtbl;

    interface _DOcxFileEvents
    {
        CONST_VTBL struct _DOcxFileEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DOcxFileEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DOcxFileEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DOcxFileEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DOcxFileEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DOcxFileEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DOcxFileEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DOcxFileEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DOcxFileEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_OcxFile,0x3F08C971,0x449F,0x4588,0x85,0x3F,0x9E,0x25,0xDD,0x73,0x87,0x9B);

#ifdef __cplusplus

class DECLSPEC_UUID("3F08C971-449F-4588-853F-9E25DD73879B")
OcxFile;
#endif
#endif /* __OCXFILELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


