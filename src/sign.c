#include <iota/internal.h>
#include <iota/iota.h>

#include <stdlib.h>
#include <string.h>

#include <curl.h>
#include <util/converter.h>

const char *iota_digests(const char *trytes) {
  int i, j, k;
  int numKeys;
  int offset;
  Curl c;
  trit_t *digest, *trits;
  char *digestTrytes;

  init_converter();
  numKeys = strlen(trytes);
  numKeys /= IOTA_FRAGMENT_LENGTH;
  if (numKeys == 0) {
    return NULL;
  }

  digest = (trit_t *)calloc(IOTA_HASHLEN_TRIT * numKeys, sizeof(trit_t));

  for (i = 0; i < numKeys; i++) {
    trits = trits_from_trytes(trytes + i * IOTA_FRAGMENT_LENGTH,
                              IOTA_FRAGMENT_LENGTH);

    for (j = 0; j < IOTA_NUMBER_OF_ROUNDS; j++) {
      offset = j * IOTA_HASHLEN_TRIT;

      for (k = 0; k < 26; k++) {
        init_curl(&c);
        absorb(&c, trits, offset, IOTA_HASHLEN_TRIT);
        squeeze(&c, trits, offset, IOTA_HASHLEN_TRIT);
      }
    }

    init_curl(&c);
    absorb(&c, trits, 0, IOTA_FRAGMENT_LENGTH * 3);
    squeeze(&c, digest, i * IOTA_HASHLEN_TRIT, IOTA_HASHLEN_TRIT);

    free((void *)trits);
  }

  digestTrytes = trytes_from_trits((trit_t * const) digest, 0,
                                   numKeys * IOTA_HASHLEN_TRIT);
  free((void *)digest);

  return digestTrytes;
}

const char *iota_checksum(const char *trytes) {
  Curl c;
  const char *hash, *checksum;

  hash = iota_curl_hash_trytes(&c, trytes, IOTA_HASHLEN_TRYTE);
  checksum = (const char *)calloc(IOTA_HASHLEN_TRYTE + IOTA_CHECKSUM_SIZE,
                                  sizeof(char));
  memcpy((void *)checksum, trytes, IOTA_HASHLEN_TRYTE * sizeof(char));
  memcpy((void *)checksum + IOTA_HASHLEN_TRYTE, hash,
         IOTA_CHECKSUM_SIZE * sizeof(char));

  free((void *)hash);

  return checksum;
}
