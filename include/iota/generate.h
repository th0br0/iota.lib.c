#pragma once

#include "export.h"

#ifdef __cplusplus
extern "C" {
#endif
  
  /**
   * Generates a new IOTA seed.
   * 
   * @warning This uses `rand()` and thus can not be expected to create a truly random seed!
   *
   * @return a valid new seed
   */
  EXPORT const char* iota_generateSeed();


  /**
   * Generates a private key for the given key index and seed.
   *
   * @param seed IOTA seed (must be a valid tryte!)
   * @param keyIndex key index
   * @param securityLevel determines number of ccurl iterations
   * @return 
   */
  EXPORT const char* iota_generateKey(const char* seed, int keyIndex, int securityLevel);


#ifdef __cplusplus
}
#endif
