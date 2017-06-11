#pragma once

#include "export.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Generates a new IOTA seed.
 *
 * @warning This uses `rand()` and thus can not be expected to create a truly
 * random seed!
 *
 * @return a valid new seed
 */
EXPORT const char *iota_generateSeed();

/**
 * Generates a private key for the given key index and seed.
 *
 * @param seed wallet seed (must be a valid tryte!)
 * @param keyIndex key index
 * @param securityLevel determines number of ccurl iterations
 * @return
 */
EXPORT const char *iota_generateKey(const char *seed, int keyIndex,
                                    int securityLevel);

/**
 * Generates an address from the given seed and key index.
 *
 * @param seed wallet seed
 * @param keyIndex @link(iota_generateKey)
 * @param securityLevel @link(iota_generateKey)
 */
EXPORT const char *iota_generateAddress(const char *seed, int keyIndex,
                                        int securityLevel);

#ifdef __cplusplus
}
#endif
