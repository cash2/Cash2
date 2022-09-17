// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "IMainChainStorage.h"
#include "Currency.h"
#include "SwappedVector.h"

namespace CryptoNote {

class MainChainStorage: public IMainChainStorage {
public:
  MainChainStorage(const std::string& blocksFilame, const std::string& indexesFilename);
  virtual ~MainChainStorage();

  virtual void pushBlock(const RawBlock& rawBlock) override;
  virtual void popBlock() override;

  virtual RawBlock getBlockByIndex(uint32_t index) const override;
  virtual uint32_t getBlockCount() const override;

  virtual void clear() override;

private:
  mutable SwappedVector<RawBlock> storage;
};

std::unique_ptr<IMainChainStorage> createSwappedMainChainStorage(const std::string& dataDir, const Currency& currency);

}
