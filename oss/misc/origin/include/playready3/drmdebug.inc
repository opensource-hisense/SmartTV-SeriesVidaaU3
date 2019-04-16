/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#define DRM_BUILDING_DRMDEBUG_C
#include <drmdebug.h>
#include <drmlicense.h>
#include <drmlastinclude.h>
#include <drmh264.h>
#include <drmrevocationtypes.h>
#include <oemteetypes.h>

ENTER_PK_NAMESPACE_CODE;

DRM_VOID DRM_TYPE_ASSERTS(void)
{
    DRMSIZEASSERT(sizeof(DRM_BYTE),         1);
    DRMSIZEASSERT(sizeof(DRM_CHAR),         1);
    DRMSIZEASSERT(sizeof(DRM_WCHAR),        2);
    DRMSIZEASSERT(sizeof(DRM_WCHAR_NATIVE), 2);
    DRMSIZEASSERT(sizeof(DRM_WORD),         2);
    DRMSIZEASSERT(sizeof(DRM_LONG),         4);
    DRMSIZEASSERT(sizeof(DRM_DWORD),        4);
    DRMSIZEASSERT(sizeof(DRM_WCHAR32),      4);
    DRMSIZEASSERT(sizeof(DRM_BOOL),         4);
    DRMSIZEASSERT(sizeof(DRM_INT64),        8);
    DRMSIZEASSERT(sizeof(DRM_UINT64),       8);

    /*
    ** Device cert and licenses will be staged to share the same buffer
    */
    DRMSIZEASSERT(MAX_DEVICE_CERT_SIZE, DRM_MAX_LICENSESIZE);

    #if DRM_SUPPORT_NATIVE_64BIT_TYPES
    /*
    ** The following constants were pre-evaluated for performance
    ** reasons. Their correctness is checked by the following asserts.
    */
    DRMCASSERT( DRM_C_SECONDS_FROM_1601_TO_1970         == DRM_UI64Mul( DRM_UI64( 1164447360 ), DRM_UI64( 10 ) ) );
    DRMCASSERT( DRM_H264_ERROR_WINDOW_IN_TICS           == DRM_UI64Mul( DRM_H264_ERROR_WINDOW_IN_SECONDS, DRM_C_TICS_PER_SECOND ) );
    DRMCASSERT( MAX_REVOCATION_EXPIRE_TICS              == DRM_UI64Mul( MAX_REVOCATION_EXPIRE_TIME, DRM_C_TICS_PER_SECOND ) );
    DRMCASSERT( MAX_ALLOWED_TIME_BEFORE_CLOCK_RESYNC    == DRM_UI64Mul( DRM_UI64( 3456000 ), DRM_UI64( DRM_C_TICS_PER_SECOND ) ) );
    #endif
}

EXIT_PK_NAMESPACE_CODE;
