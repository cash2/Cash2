// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <CryptoNoteCore/BlockchainStorage.h>
#include "CryptoNoteCore/SwappedVector.h"

namespace CryptoNote {

class SwappedBlockchainStorage : public BlockchainStorage::IBlockchainStorageInternal {
public:
  SwappedBlockchainStorage(const std::string& indexFileName, const std::string& dataFileName);
  virtual ~SwappedBlockchainStorage() override;

  virtual void pushBlock(RawBlock&& rawBlock) override;

  //Returns MemoryBlockchainStorage with elements from [splitIndex, blocks.size() - 1].
  //Original SwappedBlockchainStorage will contain elements from [0, splitIndex - 1].
  virtual std::unique_ptr<BlockchainStorage::IBlockchainStorageInternal> splitStorage(uint32_t splitIndex) override;

  virtual RawBlock getBlockByIndex(uint32_t index) const override;
  virtual uint32_t getBlockCount() const override;

private:
  mutable SwappedVector<RawBlock> blocks;
};

}
