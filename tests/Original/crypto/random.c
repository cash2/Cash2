// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string.h>
#include "crypto/hash-ops.h"
#include "crypto-tests.h"

static union hash_state state;

void setup_random(void) {
    memset(&state, 42, sizeof(union hash_state));
}
