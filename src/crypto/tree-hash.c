// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <alloca.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "hash-ops.h"

void tree_hash(const char (*hashes)[HASH_SIZE], size_t count, char *root_hash)
{
  
  assert(count > 0);

  // first hash in hashes should be the coinbase transaction hash
  memcpy(root_hash, hashes[0], HASH_SIZE);

  for (size_t h = 1; h < count; h++)
  {
    char binaryArray[2 * HASH_SIZE + 1];

    // prepend byte with value of 1 to follow Siacoin stratum protocol
    binaryArray[0] = 1;

    // append transaction hash to binary array
    memcpy(binaryArray + 1, hashes[h], HASH_SIZE);

    // append merkle root to binary array
    memcpy(binaryArray + 1 + HASH_SIZE, root_hash, HASH_SIZE);

    // hash the binary array to get the merkle root
    cn_fast_hash(binaryArray, 2 * HASH_SIZE + 1, root_hash);
  }
}

size_t tree_depth(size_t count) {
  size_t i;
  size_t depth = 0;
  assert(count > 0);
  for (i = sizeof(size_t) << 2; i > 0; i >>= 1) {
    if (count >> i > 0) {
      count >>= i;
      depth += i;
    }
  }
  return depth;
}

// TODO: will likely have to rewrite this function to match existing tree_hash function above
void tree_branch(const char (*hashes)[HASH_SIZE], size_t count, char (*branch)[HASH_SIZE]) {
  size_t i, j;
  size_t cnt = 1;
  size_t depth = 0;
  char (*ints)[HASH_SIZE];
  assert(count > 0);
  for (i = sizeof(size_t) << 2; i > 0; i >>= 1) {
    if (cnt << i <= count) {
      cnt <<= i;
      depth += i;
    }
  }
  assert(cnt == 1ULL << depth);
  assert(depth == tree_depth(count));
  ints = alloca((cnt - 1) * HASH_SIZE);
  memcpy(ints, hashes + 1, (2 * cnt - count - 1) * HASH_SIZE);
  for (i = 2 * cnt - count, j = 2 * cnt - count - 1; j < cnt - 1; i += 2, ++j) {
    cn_fast_hash(hashes[i], 2 * HASH_SIZE, ints[j]);
  }
  assert(i == count);
  while (depth > 0) {
    assert(cnt == 1ULL << depth);
    cnt >>= 1;
    --depth;
    memcpy(branch[depth], ints[0], HASH_SIZE);
    for (i = 1, j = 0; j < cnt - 1; i += 2, ++j) {
      cn_fast_hash(ints[i], 2 * HASH_SIZE, ints[j]);
    }
  }
}

// TODO: will likely have to rewrite this function to match existing tree_hash function above
void tree_hash_from_branch(const char (*branch)[HASH_SIZE], size_t depth, const char *leaf, const void *path, char *root_hash) {
  if (depth == 0) {
    memcpy(root_hash, leaf, HASH_SIZE);
  } else {
    char buffer[2][HASH_SIZE];
    int from_leaf = 1;
    char *leaf_path, *branch_path;
    while (depth > 0) {
      --depth;
      if (path && (((const char *) path)[depth >> 3] & (1 << (depth & 7))) != 0) {
        leaf_path = buffer[1];
        branch_path = buffer[0];
      } else {
        leaf_path = buffer[0];
        branch_path = buffer[1];
      }
      if (from_leaf) {
        memcpy(leaf_path, leaf, HASH_SIZE);
        from_leaf = 0;
      } else {
        cn_fast_hash(buffer, 2 * HASH_SIZE, leaf_path);
      }
      memcpy(branch_path, branch[depth], HASH_SIZE);
    }
    cn_fast_hash(buffer, 2 * HASH_SIZE, root_hash);
  }
}
