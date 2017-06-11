#pragma once

#include <curl.h>

void iota_curl_hash(Curl *curl, trit_t *trits, int offset, int length);
const char *iota_curl_hash_trytes(Curl *curl, const char *trytes, int length);
