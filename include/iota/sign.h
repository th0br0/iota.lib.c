#pragma once

#include "export.h"

#ifdef __cplusplus
extern "C" {
#endif

  /**
   *  @brief Generates the digest used to do the actual signing.
   *
   * Signing keys can have variable length and tend to be quite long,
   * which makes them not-well-suited for use in crypto algorithms.
   * 
   * The digest is essentially the result of running the signing key
   * through a PBKDF, yielding a constant-length hash that can be used
   * for crypto.
   *
   * @return NULL if input is too short
   * @return or concatenated string of all hashes
   */
  EXPORT const char* iota_digests(const char* trytes);

#ifdef __cplusplus
}
#endif
