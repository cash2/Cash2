// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "SwappedBlockchainStorage.h"

#include <cassert>

#include "CryptoNoteCore/CryptoNoteSerialization.h"
#include "ICoreDefinitions.h"
#include "MemoryBlockchainStorage.h"
#include "Serialization/SerializationOverloads.h"

namespace CryptoNote {

SwappedBlockchainStorage::SwappedBlockchainStorage(const std::string& indexFileName, const std::string& dataFileName) {
  if (!blocks.open(dataFileName, indexFileName, 1024)) {
    throw std::runtime_error("Can't open blockchain storage files.");
  }
}

SwappedBlockchainStorage::~SwappedBlockchainStorage() {
  blocks.close();
}

void SwappedBlockchainStorage::pushBlock(RawBlock&& rawBlock) {
  blocks.push_back(rawBlock);
}

RawBlock SwappedBlockchainStorage::getBlockByIndex(uint32_t index) const {
  assert(index < getBlockCount());
  return blocks[index];
}

uint32_t SwappedBlockchainStorage::getBlockCount() const {
  return static_cast<uint32_t>(blocks.size());
}

//Returns MemoryBlockchainStorage with elements from [splitIndex, blocks.size() - 1].
//Original SwappedBlockchainStorage will contain elements from [0, splitIndex - 1].
std::unique_ptr<BlockchainStorage::IBlockchainStorageInternal> SwappedBlockchainStorage::splitStorage(uint32_t splitIndex) {
  assert(splitIndex > 0);
  assert(splitIndex < blocks.size());
  std::unique_ptr<MemoryBlockchainStorage> newStorage = std::unique_ptr<MemoryBlockchainStorage>(new MemoryBlockchainStorage(splitIndex));

  uint64_t blocksCount = blocks.size();

  for (uint64_t i = splitIndex; i < blocksCount; ++i) {
    newStorage->pushBlock(RawBlock(blocks[i]));
  }

  for (uint64_t i = 0; i < blocksCount - splitIndex; ++i) {
    blocks.pop_back();
  }

  return std::move(newStorage);
}

}
