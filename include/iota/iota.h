#pragma once

/// @file iota.h
/// @file constants.h

#include <stdint.h>

#include "constants.h"

/**
 * Generates a new IOTA seed.
 * 
 * @warning This uses `rand()` and thus can not be expected to create a truly random seed!
 *
 * @return a valid new seed
 */
char* iota_generateSeed();


/**
 * Generates a private key for the given key index and seed.
 *
 * @param seed IOTA seed (must be a valid tryte!)
 * @param keyIndex key index
 * @param securityLevel determines number of ccurl iterations
 * @return 
 */
char* iota_generateKey(char* seed, uintmax_t keyIndex, uintmax_t securityLevel);


