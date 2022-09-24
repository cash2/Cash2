// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "VectorMainChainStorage.h"

#include <CryptoNoteCore/CryptoNoteTools.h>

namespace CryptoNote {

void VectorMainChainStorage::pushBlock(const RawBlock& rawBlock) {
  storage.push_back(rawBlock);
}

void VectorMainChainStorage::popBlock() {
  storage.pop_back();
}

RawBlock VectorMainChainStorage::getBlockByIndex(uint32_t index) const {
  return storage.at(index);
}

uint32_t VectorMainChainStorage::getBlockCount() const {
  return static_cast<uint32_t>(storage.size());
}

void VectorMainChainStorage::clear() {
  storage.clear();
}

std::unique_ptr<IMainChainStorage> createVectorMainChainStorage(const Currency& currency) {
  std::unique_ptr<IMainChainStorage> storage(new VectorMainChainStorage());

  RawBlock genesis;
  genesis.block = toBinaryArray(currency.genesisBlock());
  storage->pushBlock(genesis);

  return storage;
}

}
