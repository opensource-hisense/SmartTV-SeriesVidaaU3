// Copyright 2018 Google LLC. All Rights Reserved. This file and proprietary
// source code may only be used and distributed under the Widevine Master
// License Agreement.
#ifndef WVCDM_CDM_PROPERTIES_CE_H_
#define WVCDM_CDM_PROPERTIES_CE_H_

#include "cdm.h"

#if defined(UNIT_TEST)
# include <gtest/gtest.h>
#endif

namespace widevine {

class PropertiesCE {
 public:
  static Cdm::ClientInfo GetClientInfo();
  static Cdm::SecureOutputType GetSecureOutputType();
  static void SetProvisioningMessagesAreBinary(bool bin_prov);

 private:
  static void SetSecureOutputType(Cdm::SecureOutputType secure_output_type);
  static void SetClientInfo(const Cdm::ClientInfo& client_info);

  friend class Cdm;
#if defined(UNIT_TEST)
  FRIEND_TEST(CdmTest, DeviceCertificateRequest);
#endif
};

}  // namespace widevine

#endif  // WVCDM_CDM_PROPERTIES_CE_H_
