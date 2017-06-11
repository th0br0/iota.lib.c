#include <iota/iota.h>

#include <stdlib.h>

char* iota_generateSeed() {
  int i;
  char* tr = malloc(IOTA_TRYTE_LENGTH * sizeof(tryte) + 1);

  for(i = 0; i < IOTA_TRYTE_LENGTH; i++) {
    int c = rand() % IOTA_TRYTE_ALPHABET_LENGTH;
    if(c == 0) {
      tr[i] = '9';
    } else {
      tr[i] = 64 + c;
    }
  }
  tr[IOTA_TRYTE_LENGTH] = '\0';

  return tr;
}

char* iota_generateKey(char* seed, uintmax_t keyIndex, uintmax_t securityLevel) {
  return NULL;
}
