#include "gtest/gtest.h"

#include <cstdint>
#include <iostream>
#include <string>

#include <iota/internal.h>
#include <iota/iota.h>

TEST(InternalTest, Normalized) {
  auto hash = std::string("DEXRPLKGBROUQMKCLMRPG9HFKCACDZ9AB9HOJQWERTYWERJNOYLW"
                          "9PKLOGDUPC9DLGSUH9UHSKJOASJRU");
  int8_t expected[] = {-13, -13, -13, -13, -11, 12,  11, 7,   2,   -9, -12, -6,
                       -10, 13,  11,  3,   12,  13,  -9, -11, 7,   0,  8,   6,
                       11,  3,   1,   13,  13,  13,  7,  1,   2,   0,  8,   -12,
                       10,  -10, -4,  5,   -9,  -7,  -2, -4,  5,   -9, 10,  -13,
                       -12, -2,  12,  -4,  0,   -11, -5, 12,  -12, 7,  4,   -6,
                       -11, 3,   0,   4,   12,  7,   -8, -6,  8,   0,  -6,  8,
                       -8,  11,  10,  -12, 1,   -8,  10, -9,  -6};

  auto normalized = iota_normalize(hash.c_str());

  for (int i = 0; i < hash.length(); i++) {
    EXPECT_EQ(expected[i], normalized[i]);
  }

  free(normalized);
}
