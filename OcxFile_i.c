

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

MIDL_DEFINE_GUID(IID, LIBID_OCXFILELib,0x778A60AE,0xA11E,0x4DE2,0x8E,0x5C,0x13,0xC9,0x6E,0x24,0x3F,0x5B);


MIDL_DEFINE_GUID(IID, DIID__DOcxFile,0xB29222EA,0x7DB7,0x4F0A,0xAF,0x18,0x79,0x3F,0xCC,0x0F,0x23,0x09);


MIDL_DEFINE_GUID(IID, DIID__DOcxFileEvents,0xF0B787D0,0x2D92,0x4FE1,0x9D,0xF3,0xCE,0x7D,0xD3,0x0D,0xF1,0x8F);


MIDL_DEFINE_GUID(CLSID, CLSID_OcxFile,0x3F08C971,0x449F,0x4588,0x85,0x3F,0x9E,0x25,0xDD,0x73,0x87,0x9B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



