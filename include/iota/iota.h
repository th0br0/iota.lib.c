#pragma once

/// @file iota.h
/// @file constants.h

#include <stdint.h>

#include "constants.h"

#ifndef EXPORT
#if defined(_WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
#endif

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

/**
 * Validates trytes
 *
 * @param trytes trytes to validate
 * @return 0 if trytes is invalid
 * @return 1 if trytes is valid
 */
EXPORT int iota_isValidTrytes(const char* trytes);

#ifdef __cplusplus
}
#endif
