/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMCONTEXTSIZES_H__
#define __DRMCONTEXTSIZES_H__

#include <drmtypes.h>
#include <oemcryptoctx.h>
#include <drmstkalloctypes.h>
#include <drmdatastoretypes.h>
#include <drmhds.h>
#include <drmsecurestore.h>
#include <drmliceval.h>
#include <drmutilitieslite.h>
#include <drmmetercertstore.h>
#include <drmblackboxtypes.h>
#include <drmlicstore.h>
#include <drmoutputleveltypes.h>
#include <drmchaintypes.h>
#include <drmplayreadyobj.h>
#include <drmdomainstoretypes.h>
#include <drmnoncestore.h>
#include <drmprndprotocoltypes.h>
#include <drmlicgentypes.h>
#include <drmsecurecoretypes.h>
#include <drmsecurestoptypes.h>

ENTER_PK_NAMESPACE;

/* Recommended activation context size. */
#define ACTIVATION_CONTEXT_SIZE                  1024

/* The buffer should be big enough to store a single XMR license. */
#define DRM_DEFAULT_IN_MEMORY_LICENSE_SIZE       1024

/* The maximum buffer should be big enough to store 200 XMR licenses. */
#define DRM_MAX_IN_MEMORY_LICENSE_STORE_SIZE     204800

/* The maximum buffer size of an In memory SecureStore. */
#define DRM_MAX_IN_MEMORY_SECURE_STORE_SIZE      204800

/* MSTAR patch */
typedef struct TeeInfo
{
    DRM_BYTE  m_teeStartCode[4];
    // len for TEE header$
    DRM_DWORD m_teeHeaderLen;
    // application id
    DRM_DWORD m_appId;
    // kid, use to mapping to real AES key
    DRM_BYTE  m_kid[32];
} ST_TeeInfo;

typedef struct {
    DRM_DWORD mNumBytesOfClearData;
    DRM_DWORD mNumBytesOfEncryptedData;
}SubSample;

typedef struct {
    DRM_DWORD mMode;
    DRM_BYTE mKey[16];
    // UUID of the DRM system.  Refer to PIFF 5.3.1.
    DRM_BYTE mDrmId[16];
    DRM_BYTE mIv[16];
    DRM_DWORD mNumSubSamples;
    SubSample mSubSamples[1];
}CryptoInfo;

typedef struct SecureHandle{
    unsigned int secMemHandle;              // destination address of secure buffer(VDEC start address)
    unsigned int secMemLength;              // length of the secure buffer ( VDEC total length)
    unsigned int secMemOffset;              // the secure buffer offset to push the decrypted data //  (VDEC write pointer = start address + offset)
    unsigned int numberOfSubsamples;        // number of subsamples of input buffer (f_hInBuf)
    struct SubSampleEntity* subsamples;     // Array of SubSampleEntity with length of numberOfSubsamples
    unsigned long long xcid;                // xc id
    unsigned long long streamid;            // stream id
    unsigned long long pipelineid;          // pipeline id
    unsigned long long reserve[8];          // reserve
} SecureHandle_t;

struct SubSampleEntity
{
    unsigned int clearDataLength; // number of bytes of clear data in a subsample
    unsigned int cipherDataLength; // number of bytes of cipher in a subsample
};

typedef struct {
     DRM_UINT64 startAddr;
     DRM_UINT64 destAddr;
     DRM_UINT64 buffLen;
     DRM_UINT64 pipeLineID;
     DRM_UINT64 streamID;
     DRM_UINT64 xcID;
}SecureBufferHandle;

typedef enum _DRM_CONTENT_SET_PROPERTY
{
    DRM_CSP_HEADER_NOT_SET          = 0,
    DRM_CSP_V1_HEADER               = 1,
    DRM_CSP_V2_HEADER               = 2,
    DRM_CSP_KID                     = 3,
    DRM_CSP_V2_4_HEADER             = 5,
    DRM_CSP_V4_HEADER               = 6,
    DRM_CSP_AUTODETECT_HEADER       = 7,
    DRM_CSP_PLAYREADY_OBJ           = 8,
    DRM_CSP_V4_1_HEADER             = 9,
    DRM_CSP_PLAYREADY_OBJ_WITH_KID  = 10,
    DRM_CSP_HEADER_COMPONENTS       = 11,
    DRM_CSP_V4_2_HEADER             = 12,
    DRM_CSP_DECRYPTION_OUTPUT_MODE  = 13,
    DRM_CSP_SELECT_KID              = 14,
} DRM_CONTENT_SET_PROPERTY;

typedef enum _DRM_CONTENT_GET_PROPERTY
{
    DRM_CGP_HEADER_KID              = 0,
    DRM_CGP_HEADER_TYPE             = 1,
    DRM_CGP_HEADER                  = 2,
    DRM_CGP_PLAYREADY_OBJ           = 3,
    DRM_CGP_CIPHER_TYPE             = 4,
    DRM_CGP_DECRYPTORSETUP          = 5,
    DRM_CGP_HEADER_KIDS             = 6,
    DRM_CGP_DECRYPTION_OUTPUT_MODE  = 7,
} DRM_CONTENT_GET_PROPERTY;

typedef struct __tagDRM_APP_CONTEXT_INTERNAL
{
    DRM_BOOL                    fLicStoreOpenXMR;
    DRM_BOOL                    fSecStoreGlobalContextOpen;
    DRM_CONTENT_SET_PROPERTY    eHeaderInContext;
    DRM_BOOL                    fCanBind;

    DRM_BOOL                    fResponseSignatureChecked;
    DRM_DWORD                   dwLastResponseProtocol;

    DRM_VOID                   *pOEMContext;

    DRM_KID                     KID;

    DRM_BINDING_INFO            oBindInfo[DRM_MAX_LICENSE_CHAIN_DEPTH];
    DRM_XMRFORMAT               licenseXMR[DRM_MAX_LICENSE_CHAIN_DEPTH];

    DRM_LICSTORE_CONTEXT        oLicStoreContextXMR;
    DRM_LICSTORE_CONTEXT        oLicStoreContextEmbedded;
    DRM_LICSTOREENUM_CONTEXT    oLicEnum[DRM_MAX_LICENSE_CHAIN_DEPTH];
    DRM_LICSTOREENUM_MULTIPLE_CONTEXT oLicEnumMultiple[DRM_MAX_LICENSE_CHAIN_DEPTH];

    DRM_LICEVAL_CONTEXT         oLicEvalContext;
    DRM_SECSTORE_CONTEXT        oSecStoreGlobalContext;

    DRM_DWORD                   dwChainDepth;
    DRM_SECSTORE_CONTEXT        rgcontextSST[DRM_MAX_LICENSE_CHAIN_DEPTH];

    DRM_SECSTORE_CONTEXT        contextSSTCertCache;

    DRM_REVLIST_ID_VALUES        idCRLsCurrent;
    DRM_REVOCATIONSTORE_CONTEXT  oRevContext;

    DRM_BYTE                    *pbRevocationBuffer;
    DRM_DWORD                    cbRevocationBuffer;

    DRM_FFLICENSE                oFFLicense;
    DRM_METERCERT_CONTEXT        oMeterCertContext;
    DRM_DST                      oDatastoreHDS;
    DRM_HDS_CONTEXT              oContextHDS;
    DRM_DST                      oDatastoreEST;
    DRM_EST_CONTEXT              oContextEST;
    DRM_BOOL                     fStoreOpened;

    DRM_BYTE                    *pbOpaqueBuffer;
    DRM_DWORD                    cbOpaqueBuffer;
    DRM_BYTE                    *pbDRMHeaderData;  /* Should always point to the start of pbOpaqueBuffer */
    DRM_DWORD                    cbDRMHeaderData;  /* Should always be cbOpaqueBuffer - DRM_DWORD_ALIGNED_SIZE( DRM_MAX_LICENSESIZE ) */
    DRM_BYTE                    *pbDRMLicense;    /* Should always point to the last DRM_DWORD_ALIGNED_SIZE( DRM_MAX_LICENSESIZE ) bytes of pbOpaqueBuffer */
    DRM_DWORD                    cbDRMLicense;    /* Should always be DRM_DWORD_ALIGNED_SIZE( DRM_MAX_LICENSESIZE ) */

    DRM_WCHAR                   *pwszHeaderData;  /* Used with pbDRMHeaderData: Points into the PRO at the V4 header */
    DRM_DWORD                    cbHeaderData;
    DRM_BYTE                    *pbEmbeddedStore; /* Used with pbDRMHeaderData: Points into the PRO at the embedded store */
    DRM_DWORD                    cbEmbeddedStore;
    DRM_DWORD                    cbPROData;       /* Used with pbDRMHeaderData: Specifies the length of the entire PRO if it is set  */
    DRM_DWORD                    cbTotalHeaderData; /* Used with pbDRMHeaderData: Specifies the total length of the buffer filled with header data or PRO data */

    DRM_BOOL                     fClockSet;
    DRM_BOOL                     fBindThenCommit;
    DRM_DWORD                    dwSourceid;

    DRM_DWORD                    dwLicRevInfoVer;

    DRM_DOMAINSTORE_CONTEXT      oDomainStoreContext;
    DRM_LICSTORE_CONTEXT         oLicStoreContextNST;
    DRM_NONCESTORE_CONTEXT       oNonceStoreContext;

    DRM_DWORD                    cbNSTBuffer;
    DRM_BYTE                    *pbNSTBuffer;

    DRM_CHAR                     szClientVersion[DRM_VER_STRING_MAX_LEN];
    DRM_BYTE                    *pbActivationCtx;

    DRM_PRND_TRANSMITTER_CONTEXT    *poPrndTransmitterContext;
    DRM_PRND_RECEIVER_CONTEXT       *poPrndReceiverContext;
    DRM_BOOL                         fPRNDRxLSTOpened;
    DRM_LICSTORE_CONTEXT             oLSTContextPRNDRxStore;
    DRM_DST                          oDSTContextPRNDRxStore;
    DRM_EST_CONTEXT                  oESTContextPRNDRxStore;
    DRM_BYTE                         rgbPRNDRxStore[SIZE_OF_PLAYREADY_EMBEDDED_LICENSE_SPACE];

    DRM_DST                          oDSTContextMemSST;
    DRM_EST_CONTEXT                  oESTContextMemSST;
    DRM_BYTE                        *pbMemSSTStore;
    DRM_DWORD                        cbMemSSTStore;

    DRM_LOCAL_LICENSE_CONTEXT       *poLocalLicenseContext;

    DRM_SECURECORE_CONTEXT           oSecureCoreCtx;
    DRM_DWORD                        dwDecryptionOutputMode;   /* Refer to the member with the same name in DRM_FFLICENSE */

    DRM_SECURESTOP_CONTEXT           oSecureStopCtx;

} DRM_APP_CONTEXT_INTERNAL;

#define DRM_APP_CONTEXT_BUFFER_SIZE        sizeof( DRM_APP_CONTEXT_INTERNAL )

EXIT_PK_NAMESPACE;

#endif /* __DRMCONTEXTSIZES_H__ */

