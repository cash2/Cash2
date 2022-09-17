// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once 

#include <CryptoNote.h>

namespace CryptoNote {

class IMainChainStorage {
public:
  virtual ~IMainChainStorage() { }

  virtual void pushBlock(const RawBlock& rawBlock) = 0;
  virtual void popBlock() = 0;

  virtual RawBlock getBlockByIndex(uint32_t index) const = 0;
  virtual uint32_t getBlockCount() const = 0;

  virtual void clear() = 0;
};

}
