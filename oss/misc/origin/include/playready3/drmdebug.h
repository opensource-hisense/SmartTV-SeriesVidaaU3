/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMDEBUG_H__
#define __DRMDEBUG_H__

#include <oemdebug.h>

ENTER_PK_NAMESPACE;

/*************************************************************************
*
*   debug printf macro
*   Sample calling seq:
*
*   TRACE(("My name is %s", "DRM"));
*
*   Note the double parenthesis.
*************************************************************************/
#if DRM_DBG

    #undef TRACE

    #ifdef __cplusplus_cli
        // If building under a C++/CLI flag ignore all TRACE statements
        #define TRACE(x)
    #else
        #define TRACE(x) do { Oem_Debug_Trace("TRACE at %s(%d): ", __FILE__, __LINE__); Oem_Debug_Trace x; Oem_Debug_Trace("\r\n"); } while( FALSE )
    #endif

    #undef TRACE_IF_FAILED
    #define TRACE_IF_FAILED(x) do { if ( DRM_FAILED( dr ) ){ TRACE(x); } } while ( FALSE )

    /*
    ** Set to 1 to enable maximum TEE heap usage logging for PC builds using the simulated TEE HWDRM.
    ** The log file (defined by DRM_TEE_HEAP_USAGE_LOG_FILE in oemdiagheaplogger.cpp) will be located
    ** next to the HDS file in the PlayReady Metro directory.
    */
    #define DRM_PC_USE_TEE_HEAP_USAGE_DIAGNOSITCS 0

    #if DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_PC && DRM_PC_USE_TEE_HEAP_USAGE_DIAGNOSITCS == 1
        #define DRM_PC_TEST_CAPTURE_TEE_HEAP_USAGE 1
        #define DRM_PC_TEST_CAPTURE_TEE_HEAP_MOCK ENTER_PK_NAMESPACE; DRM_DWORD g_dwCurrentTeeFunctionID = 0; EXIT_PK_NAMESPACE;
    #else
        #define DRM_PC_TEST_CAPTURE_TEE_HEAP_USAGE 0
        #define DRM_PC_TEST_CAPTURE_TEE_HEAP_MOCK
    #endif

#else  /* DRM_DBG */

    #define DRM_PC_TEST_CAPTURE_TEE_HEAP_USAGE 0
    #define DRM_PC_TEST_CAPTURE_TEE_HEAP_MOCK

    #ifndef TRACE
    #define TRACE(x)
    #endif

    #ifndef TRACE_IF_FAILED
    #define TRACE_IF_FAILED(x)
    #endif

#endif  /* DRM_DBG */


/*
** Compile-time asserts cause PREfast warnings regarding the comparison of two constants.
** So, enable this macro only when the PREfast tool is not analyzing the code.
*/
#ifndef _PREFAST_
    #define DRMSIZEASSERT(x,y)  \
        {switch(0){case ((x)==(y)?0:(y)):case (y):;}} \
        {switch(0){case ((y)==(x)?0:(x)):case (x):;}}
#else
    #define DRMSIZEASSERT(x,y)
#endif


#define ENSURE_MEMBERS_ADJACENT(struc,member1,member2)  ((DRM_OFFSET_OF(struc,member1)+(DRM_DWORD)(sizeof(((struc *)0)->member1))) == DRM_OFFSET_OF(struc,member2))

#if DRM_DBG
    #undef DRMASSERT
    /* Call the global assert handler function. */

    #ifdef __cplusplus_cli
        /* Don't include strings in C++/CLI code */
        #define DRMASSERT(x) Oem_Debug_Assert((x), NULL, NULL, __LINE__)
    #else
        #define DRMASSERT(x) Oem_Debug_Assert((x), #x, __FILE__, __LINE__)
    #endif

#else /* DRM_DBG */
    #ifndef DRMASSERT
        #define DRMASSERT( x )
    #endif
    #ifndef DRMCASSERT
        #define DRMCASSERT( x )
    #endif
#endif /* DRM_DBG */

EXIT_PK_NAMESPACE;

#endif  /* __DRMDEBUG_H__ */

