#include <iota/iota.h>
#include <string.h>

int iota_isValidTrytes(const char *const trytes) {
  int i;
  int length = strlen(trytes);

  if (length != IOTA_HASHLEN_TRYTE) {
    return 1;
  }

  for (i = 0; i < length; i++) {
    char c = trytes[i];

    if (!(c == '9' || (c >= 'A' && c <= 'Z'))) {
      return 0;
    }
  }

  return 1;
}
