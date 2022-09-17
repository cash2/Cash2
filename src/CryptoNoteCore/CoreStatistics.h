// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "Serialization/ISerializer.h"

namespace CryptoNote {

struct CoreStatistics {
  uint64_t transactionPoolSize;
  uint64_t blockchainHeight;
  uint64_t miningSpeed;
  uint64_t alternativeBlockCount;
  std::string topBlockHashString;

  void serialize(ISerializer& s) {    
    s(transactionPoolSize, "tx_pool_size");
    s(blockchainHeight, "blockchain_height");
    s(miningSpeed, "mining_speed");
    s(alternativeBlockCount, "alternative_blocks");
    s(topBlockHashString, "top_block_id_str");
  }
};

}
