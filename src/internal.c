#include <iota/internal.h>
#include <iota/iota.h>

#include <util/converter.h>

#include <stdint.h>
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

int64_t trits2int(trit_t *trits, int len) {
  int i;
  int64_t val;
  val = 0;
  for (i = len - 1; i >= 0; i--) {
    val = val * 3 + trits[i];
  }

  return val;
}

int8_t *iota_normalize(const char *trytes) {
  int i, j, idx;
  int len, sum;
  int8_t *normalized;
  trit_t *trits;

  len = strlen(trytes);

  trits = trits_from_trytes(trytes, len);
  normalized = malloc(len * sizeof(int8_t));

  sum = 0;

  for (i = 0; i < (len / 27 /* CHUNK_SIZE */); i++) {
    for (j = 0; j < 27; j++) {
      idx = i * 27 + j;
      normalized[idx] = trits2int(trits + idx * 3, 3);
      sum += normalized[idx];
    }

    if (sum >= 0) {
      for (; sum > 0; sum--) {
        for (j = 0; j < 27; j++) {
          idx = i * 27 + j;
          if (normalized[idx] > -13) {
            normalized[idx]--;
            break;
          }
        }
      }
    } else {
      for (; sum < 0; sum++) {
        for (j = 0; j < 27; j++) {
          idx = i * 27 + j;
          if (normalized[idx] < 13) {
            normalized[idx]++;
            break;
          }
        }
      }
    }
  }

  free((void *)trits);

  return normalized;
}
