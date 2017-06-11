#include "gtest/gtest.h"

#include <iostream>
#include <string>

#include <iota/iota.h>

TEST(SignTest, Digests) {
  auto expectedTrytes = "P9ZFUIEJXGKJHZBNDQHYGJCACVNZHP9FBADFDCIVPQHTOWMKJJPUVXESGKTDVLRONDAXFEBYECRRESHTCBXZDRHM9EFGWGQVSS9KDHEBDXMFYTQHCANZZZYEVWHTWGTNSNAKCTJWPQQDLXUCQJAYRWSTAUZFSHFXCQ";
  auto seed = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
              "AAAAAAAAAAAAAAAAA";
  auto computed = std::string(iota_generateKey(seed, 0, 2));
  auto digests = std::string(iota_digests(computed.c_str()));

  EXPECT_EQ(digests, expectedTrytes);
}
