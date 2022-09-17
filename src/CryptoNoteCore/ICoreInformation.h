// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once
#include <cstdint>

namespace CryptoNote {

class ICoreInformation {
public:
  virtual ~ICoreInformation() {}

  virtual size_t getPoolTransactionCount() const = 0;
  virtual size_t getBlockchainTransactionCount() const = 0;
  virtual size_t getAlternativeBlockCount() const = 0;
  virtual uint64_t getTotalGeneratedAmount() const = 0;
  virtual std::vector<BlockTemplate> getAlternativeBlocks() const = 0;
  virtual std::vector<Transaction> getPoolTransactions() const = 0;
};

}
