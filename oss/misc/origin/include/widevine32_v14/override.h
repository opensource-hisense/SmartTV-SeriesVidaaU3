// Copyright 2018 Google LLC. All Rights Reserved. This file and proprietary
// source code may only be used and distributed under the Widevine Master
// License Agreement.
// TODO: Import to core/, use everywhere.
#ifndef WVCDM_CDM_OVERRIDE_H_
#define WVCDM_CDM_OVERRIDE_H_

#define GCC_HAS_OVERRIDE ( \
  (__GNUC__ > 4) || \
  (__GNUC__ == 4 && __GNUC_MINOR__ >= 7) \
)

#if !defined(DISABLE_OVERRIDE_KEYWORD) && \
    (defined(COMPILER_MSVC) || defined(__clang__) || GCC_HAS_OVERRIDE)
#define OVERRIDE override
#else
#define OVERRIDE
#endif

#endif  // WVCDM_CDM_OVERRIDE_H_
