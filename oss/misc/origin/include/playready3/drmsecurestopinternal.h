/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMSECURESTOPINTERNAL_H_
#define _DRMSECURESTOPINTERNAL_H_ 1

#include <oemciphertypes.h>
#include <drmbytemanip.h>
#include <drmsecurecoretypes.h>
#include <drmsecurestoretypes.h>
#include <drmsecurestoptypes.h>

ENTER_PK_NAMESPACE;

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_Initialize(
    __in                                        DRM_APP_CONTEXT            *f_pAppContext );

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_UnInitialize(
    __inout                                     DRM_APP_CONTEXT            *f_pAppContext );

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_ParseAndVerifyPublisherCert(
    __in                                        DRM_APP_CONTEXT_INTERNAL   *f_pInternal,
    __in                                  const DRM_DWORD                   f_cbPublisherCert,
    __in_bcount(f_cbPublisherCert)        const DRM_BYTE                   *f_pbPublisherCert,
    __out_opt                                   DRM_ID                     *f_pidPublisher,
    __out_opt                                   PUBKEY_P256                *f_pPublicKey );

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_GetSessionByLicenseID(
    __in                                        DRM_SECURESTOP_CONTEXT     *f_pSecureStop,
    __in                                  const DRM_LID                    *f_pLicenseID,
    __deref_out_ecount(1)                       DRM_SECURESTOP_SESSION    **f_ppSession );

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_GetSessionBySessionID(
    __in                                        DRM_SECURESTOP_CONTEXT     *f_pSecureStop,
    __in                                  const DRM_ID                     *f_pSessionID,
    __out                                       DRM_SECURESTOP_SESSION    **f_ppSession );

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_CloseSessionDecryptors(
    __inout                                     DRM_APP_CONTEXT            *f_pAppContext,
    __inout                                     DRM_SECURESTOP_SESSION     *f_pSession );

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_CloseAllDecryptors(
    __inout                                     DRM_APP_CONTEXT            *f_pAppContext );

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_CreateSession(
    __in                                        DRM_APP_CONTEXT            *f_pAppContext,
    __in_opt                              const DRM_ID                     *f_pidPublisher,
    __in_opt                              const DRM_ID                     *f_pidSession,
    __in                                  const DRM_DWORD                   f_cidLicenses,
    __in_ecount_opt(f_cidLicenses)        const DRM_LID                    *f_pidLicenses );

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_BindDecryptor(
    __in                                        DRM_APP_CONTEXT            *f_pAppContext,
    __inout                                     DRM_CIPHER_CONTEXT         *f_pCipherContext );

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_UpdateSession(
    __inout                                     DRM_CIPHER_CONTEXT         *f_pCipherContext );

DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_SECURESTOP_INTERNAL_UnbindDecryptor(
    __inout                                     DRM_CIPHER_CONTEXT         *f_pCipherContext );

EXIT_PK_NAMESPACE;

#endif /* _DRMSECURESTOPINTERNAL_H_ */
