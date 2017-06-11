#pragma once

#include "export.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Validates trytes
 *
 * @param trytes trytes to validate
 * @return 0 if trytes is invalid
 * @return 1 if trytes is valid
 */
EXPORT int iota_isValidTrytes(const char *trytes);

#ifdef __cplusplus
}
#endif
