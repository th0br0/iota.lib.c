#include <iota/internal.h>
#include <iota/iota.h>

#include <util/converter.h>

#include <string.h>

void iota_curl_hash(Curl *curl, trit_t *trits, int offset, int length) {
  init_curl(curl);
  absorb(curl, trits, 0, length);
  squeeze(curl, trits, 0, length);
}

const char *iota_curl_hash_trytes(Curl *curl, const char *trytes, int len) {
  trit_t *trits;

  init_converter();
  trits = trits_from_trytes(trytes, strlen(trytes));

  iota_curl_hash(curl, trits, 0, len * 3);

  return trytes_from_trits(trits, 0, len * 3);
}
