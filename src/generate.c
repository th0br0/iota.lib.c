#include <iota/iota.h>

#include <stdlib.h>
#include <string.h>

#include <curl.h>
#include <util/converter.h>

const char *iota_generateSeed() {
  int i;
  char *tr = malloc(IOTA_HASHLEN_TRIT * sizeof(char) + 1);

  for (i = 0; i < IOTA_HASHLEN_TRIT; i++) {
    int c = rand() % IOTA_TRYTE_ALPHABET_LENGTH;
    if (c == 0) {
      tr[i] = '9';
    } else {
      tr[i] = 64 + c;
    }
  }
  tr[IOTA_HASHLEN_TRIT] = '\0';

  return tr;
}

const char *iota_generateKey(const char *seed, int keyIndex,
                             int securityLevel) {
  int i, j, len;
  Curl curl;
  char *key;
  trit_t *trits, *keyTrits;

  init_converter();

  if (!iota_isValidTrytes(seed)) {
    return NULL;
  }

  trits = trits_from_trytes(seed, IOTA_HASHLEN_TRYTE);
  for (i = 0; i < keyIndex; i++) {
    for (j = 0; j < IOTA_HASHLEN_TRIT; j++) {
      trits[j]++;
      if (trits[j] > 1) {
        trits[j] = -1;
      } else {
        break;
      }
    }
  }

  init_curl(&curl);
  absorb(&curl, trits, 0, IOTA_HASHLEN_TRIT);
  squeeze(&curl, trits, 0, IOTA_HASHLEN_TRIT);

  init_curl(&curl);
  absorb(&curl, trits, 0, IOTA_HASHLEN_TRIT);
  len = IOTA_HASHLEN_TRIT * NUMBER_OF_ROUNDS * securityLevel;

  keyTrits = (trit_t *)calloc(len, sizeof(trit_t));
  for (i = 0; i < securityLevel; i++) {
    for (j = 0; j < NUMBER_OF_ROUNDS; j++) {
      memcpy((void *)(keyTrits + ((i * NUMBER_OF_ROUNDS + j) * IOTA_HASHLEN_TRIT)),
             curl.state, IOTA_HASHLEN_TRIT * sizeof(trit_t));
      squeeze(&curl, trits, 0, IOTA_HASHLEN_TRIT);
    }
  }

  key = trytes_from_trits((trit_t * const) keyTrits, 0, len);

  free((void *)trits);
  free((void *)keyTrits);

  return key;
}
