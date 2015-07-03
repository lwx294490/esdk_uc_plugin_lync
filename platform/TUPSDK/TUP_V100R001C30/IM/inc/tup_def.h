/*****************************************************************************/
/*                Copyright 2014 - 2014, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/* FileName: tup_def.h                                                     */
/* Version:                                                               */
/* Description:                                                               */
/*                                                                           */
/* History:                                                                  */
/*                           */
/*****************************************************************************/

#ifndef __TUP_DEF_H__
#define __TUP_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */



/************************* MACRO & TYPE DEFINITION ***************************/

#define TUP_SUCCESS             (0)
#define TUP_FAIL                (1)

#define TUP_TRUE                (1)
#define TUP_FALSE               (0)

/* tup error code generation rule£º
   TUP_ERR_SECTION & ERR_SUB_SECTION & INTERNAL_SUB_SECTION & INTERNAL_ERR_CODE
   TUP_ERR_SECTION: fixed to 0x80000000UL
   ERR_SUB_SECTION: use 3 bits, from 14-16, e.g. call modular is 1, im modular is 3
   INTERNAL_SUB_SECTION:use 5bits, from 9-13, defined by each modular
*/
#define TUP_ERR_SECTION         0x08UL << 24
#define TUP_CALL_ERR_SUB_SECTION    0x01UL << 13
#define TUP_IM_ERR_SUB_SECTION      0x03UL << 13



typedef unsigned char           TUP_UINT8;
typedef char                    TUP_INT8;
typedef unsigned char           TUP_UCHAR;
typedef char                    TUP_CHAR;

typedef unsigned short          TUP_UINT16;
typedef signed short            TUP_INT16;


typedef unsigned int            TUP_UINT32;
typedef signed int              TUP_INT32;

typedef unsigned int            TUP_UINT;
typedef int                     TUP_INT;

typedef unsigned int            TUP_BOOL;

typedef unsigned long long      TUP_UINT64;
typedef long long               TUP_INT64;
typedef unsigned long           TUP_ULONG;
typedef signed long             TUP_LONG;

typedef float                   TUP_FLOAT;

//typedef void                    TUP_VOID;
#define TUP_VOID void
typedef TUP_INT32               TUP_RESULT;


#define TUP_IN
#define TUP_OUT

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif


#ifdef WIN32  

#ifdef TUP_API
#undef TUP_API
#endif

#ifdef TUP_EXPORT
#define TUP_API __declspec(dllexport)
#else
#define TUP_API __declspec(dllimport)
#endif

#else /*WIN32*/
#define TUP_API    
#endif




#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __VTOP_TYPES_H__ */


