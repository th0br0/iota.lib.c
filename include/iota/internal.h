#pragma once

#include <curl.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void iota_curl_hash(Curl *curl, trit_t *trits, int offset, int length);
const char *iota_curl_hash_trytes(Curl *curl, const char *trytes, int length);
int8_t* iota_normalize(const char* trytes);
int64_t trits2int(trit_t* trits, int len);


#ifdef __cplusplus
}
#endif
