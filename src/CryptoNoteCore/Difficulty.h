// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>
#include <vector>

#include "crypto/hash.h"

namespace CryptoNote
{
    typedef std::uint64_t Difficulty;

    bool check_hash1(const Crypto::Hash &hash, Difficulty difficulty);
    bool check_hash2(const Crypto::Hash &hash, Difficulty difficulty);
}
