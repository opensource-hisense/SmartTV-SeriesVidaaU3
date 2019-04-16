/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_NONCE_STORE_H
#define __DRM_NONCE_STORE_H

#include <drmdatastoretypes.h>
#include <drmembeddedstore_impl.h>
#include <drmlicstore.h>
#include <drmmodulesupport.h>

ENTER_PK_NAMESPACE;

/* Define the maximum number of tokens that could be associated with the nonce store */
#define DRM_MAX_NST_TOKEN_COUNT 100

/* The data structure of a nonce token. */
typedef struct _tag_DRM_NONCE_TOKEN
{
    /* Nonce value. */
    DRM_ID m_oNonce;

    /* Flag indicating how many licenses have been associated with the token. */
    DRM_DWORD m_cAllocated;

    /* Indicate wether the token is used or not */
    DRM_BOOL m_fUsed;
} DRM_NONCE_TOKEN;

/* The context of the nonce store. */
typedef struct _tagDRM_NONCESTORE_CONTEXT_INTERNAL
{
    /* Pointer to an OEM context. */
    DRM_VOID *m_pvOEMContext;

    /* Data store context. */
    DRM_DST m_oDataStore;

    /* Data store context using embedded store implementation. */
    DRM_EST_CONTEXT m_oESTContext;

    /* License store context. */
    DRM_LICSTORE_CONTEXT *m_poLicStoreContext;

    /* Nonce store buffer. */
    DRM_BYTE *m_pbBuffer;

    /* Size of nonce store buffer. */
    DRM_DWORD m_cbBuffer;

    /* Flag indicating whether this structure is initialized. */
    DRM_BOOL m_fInited;

    /* List of nonce tokens. */
    DRM_NONCE_TOKEN *m_pTokens[DRM_MAX_NST_TOKEN_COUNT];

    /* Count of Tokens currently allocated */
    DRM_DWORD m_countTokensAllocated;

    DRM_DWORD m_dwWriteIndex;
} DRM_NONCESTORE_CONTEXT_INTERNAL;

/* The context of the nonce store in the form of a BLOB. */
typedef struct __tagDRM_NONCESTORE_CONTEXT
{
    DRM_BYTE rgbOpaqueData[ sizeof( DRM_NONCESTORE_CONTEXT_INTERNAL ) ];
} DRM_NONCESTORE_CONTEXT;

DRM_API DRM_RESULT DRM_CALL DRM_NST_Open(
    __in_opt DRM_VOID *f_pvOEMContext,
    __in_bcount( f_cbNonceStore ) DRM_BYTE *f_pbNonceStore,
    __in DRM_DWORD f_cbNonceStore,
    __out DRM_LICSTORE_CONTEXT *f_poLicStoreContext,
    __out DRM_NONCESTORE_CONTEXT *f_poNonceStore );

DRM_API DRM_RESULT DRM_CALL DRM_NST_Close(
    __in DRM_NONCESTORE_CONTEXT *f_poNonceStore );

DRM_API DRM_RESULT DRM_CALL DRM_NST_SetNonce(
    __in      DRM_NONCESTORE_CONTEXT *f_poNonceStore,
    __in      DRM_ID                 *f_poNonce );

DRM_API DRM_RESULT DRM_CALL DRM_NST_AddLicense(
    __in                            DRM_NONCESTORE_CONTEXT  *f_poNonceStore,
    __in                            DRM_DWORD                f_cbLicense,
    __in_bcount( f_cbLicense )      DRM_BYTE                *f_pbLicense,
    __in const                      DRM_KID                 *f_poKID,
    __in const                      DRM_LID                 *f_poLID,
    __in                            DRM_DWORD                f_dwPriority,
    __out_opt                       DRM_ID                  *f_poBatchID );

DRM_API DRM_RESULT DRM_CALL DRM_NST_DeleteLicenses(
    __in_ecount(1)                  DRM_NONCESTORE_CONTEXT  *f_poNonceStore,
    __in_ecount(1)            const DRM_ID                  *f_poBatchID );

DRM_API DRM_RESULT DRM_CALL DRM_NST_DeleteLicenseByKID(
    __in_ecount(1)                  DRM_NONCESTORE_CONTEXT *f_poNonceStore,
    __in_ecount(1)            const DRM_KID                *f_pKID,
    __inout_opt                     DRM_DWORD              *f_pcLicDeleted );

DRM_API DRM_RESULT DRM_CALL DRM_NST_GetLicenses(
    __in_ecount(1)                          DRM_NONCESTORE_CONTEXT *f_poNonceStore,
    __in_ecount(1)                    const DRM_ID                 *f_poBatchID,
    __inout                                 DRM_DWORD              *f_pcLicenses,
    __out_ecount_opt(*f_pcLicenses)         DRM_LID                *f_pLicenses );


EXIT_PK_NAMESPACE;

#endif /* __DRM_NONCE_STORE_H */
