

#ifndef SECURE_HANDLE_H_
#define SECURE_HANDLE_H_

#include "stdio.h"
#define Secure_Handle_Version 0

#ifdef __cplusplus
extern "C" {
#endif


struct SubSampleEntity
{
    unsigned int clearDataLength; // number of bytes of clear data in a subsample
    unsigned int cipherDataLength; // number of bytes of cipher in a subsample
};

struct SecureHandle{
    SecureHandle(): version(Secure_Handle_Version) {}           //version control
    const unsigned int version;             //secureHandle structure version
    unsigned int secMemHandle;              // destination address of secure buffer(VDEC start address)
    unsigned int secMemLength;              // length of the secure buffer ( VDEC total length)
    unsigned int secMemOffset;              // the secure buffer offset to push the decrypted data //  (VDEC write pointer = start address + offset)
    unsigned int numberOfSubsamples;        // number of subsamples of input buffer (f_hInBuf)
    struct SubSampleEntity* subsamples;     // Array of SubSampleEntity with length of numberOfSubsamples
    unsigned long long xcid;                // xc id
    unsigned long long streamid;            // stream id
    unsigned long long pipelineid;          // pipeline id
    unsigned long long reserve[8];          // reserve
};

#ifdef __cplusplus
}
#endif

#endif//SECURE_HANDLE_H_
