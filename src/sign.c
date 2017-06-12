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
  checksum = (const char *)calloc(IOTA_HASHLEN_TRYTE + IOTA_CHECKSUM_SIZE + 1,
                                  sizeof(char));
  memcpy((void *)checksum, trytes, IOTA_HASHLEN_TRYTE * sizeof(char));
  memcpy((void *)checksum + IOTA_HASHLEN_TRYTE, hash,
         IOTA_CHECKSUM_SIZE * sizeof(char));

  free((void *)hash);

  return checksum;
}

const char *iota_sign(const int8_t *normalizedFragment, const char *keyTrytes) {
  int i, j, idx;
  char *signedFragment, *hashed;
  Curl c;

  signedFragment = (char *)calloc(
      IOTA_NUMBER_OF_ROUNDS * IOTA_HASHLEN_TRYTE + 1, sizeof(char));

  for (i = 0; i < IOTA_NUMBER_OF_ROUNDS; i++) {
    idx = i * IOTA_HASHLEN_TRYTE;

    memcpy(signedFragment + idx, keyTrytes + idx, IOTA_HASHLEN_TRYTE);
    for (j = 0; j < 13 - normalizedFragment[i]; j++) {
      hashed = (char *)iota_curl_hash_trytes(&c, signedFragment + idx,
                                             IOTA_HASHLEN_TRYTE);
      memcpy(signedFragment + idx, hashed, IOTA_HASHLEN_TRYTE);
      free((void *)hashed);
    }
  }

  return signedFragment;
}

char *digest(int8_t *normalized, const char *signFrag) {
  int i, j, len;
  Curl c, d;
  trit_t *trits, *tmp;
  char *digested;

  len = strnlen(signFrag, IOTA_NUMBER_OF_ROUNDS * IOTA_HASHLEN_TRYTE);
  if (len != IOTA_NUMBER_OF_ROUNDS * IOTA_HASHLEN_TRYTE) {
    return NULL;
  }

  trits = trits_from_trytes(signFrag, len);
  tmp = (trit_t *)malloc(IOTA_HASHLEN_TRIT * sizeof(trit_t));

  init_curl(&d);
  for (i = 0; i < IOTA_NUMBER_OF_ROUNDS; i++) {
    memcpy(tmp, trits + i * IOTA_HASHLEN_TRIT,
           IOTA_HASHLEN_TRIT * sizeof(trit_t));

    for (j = normalized[i] + 13; j > 0; j--) {
      iota_curl_hash(&c, tmp, 0, IOTA_HASHLEN_TRIT);
    }

    absorb(&d, tmp, 0, IOTA_HASHLEN_TRIT);
  }

  squeeze(&d, trits, 0, IOTA_HASHLEN_TRIT);

  digested = trytes_from_trits(trits, 0, IOTA_HASHLEN_TRIT);
  free((void *)trits);
  free((void *)tmp);

  return digested;
}

char iota_validateSignature(const char *address, const char **signFrags,
                            size_t len, const char *bundleHash) {
  int offset, i;
  int8_t *normalizedBundle;
  char *digests, *buf, *hashed;
  Curl c;

  digests = (char *)calloc(len * IOTA_HASHLEN_TRYTE, sizeof(char));
  normalizedBundle = iota_normalize(bundleHash);

  for (i = 0; i < len; i++) {
    offset = i * 27 * (i % 3);
    buf = digest(normalizedBundle + offset, signFrags[i]);
    memcpy(digests + i * IOTA_HASHLEN_TRYTE, buf, IOTA_HASHLEN_TRYTE);
    free((void *)buf);
  }

  hashed = (char *)iota_curl_hash_trytes(&c, digests, IOTA_HASHLEN_TRYTE * len);
  free((void *)digests);

  digests = (char *)iota_checksum(hashed);
  i = strncmp(digests, address, IOTA_HASHLEN_TRYTE + IOTA_CHECKSUM_SIZE);

  free((void *)hashed);
  free((void *)normalizedBundle);
  free((void *)digests);

  return i;
}
