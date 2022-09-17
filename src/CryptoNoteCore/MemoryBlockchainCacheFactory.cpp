// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "MemoryBlockchainCacheFactory.h"

namespace CryptoNote {

MemoryBlockchainCacheFactory::MemoryBlockchainCacheFactory(const std::string& filename, Logging::ILogger& logger):
  filename(filename), logger(logger) {
}

MemoryBlockchainCacheFactory::~MemoryBlockchainCacheFactory() {
}

std::unique_ptr<IBlockchainCache> MemoryBlockchainCacheFactory::createRootBlockchainCache(const Currency& currency) {
  return createBlockchainCache(currency, nullptr, 0);
}

std::unique_ptr<IBlockchainCache> MemoryBlockchainCacheFactory::createBlockchainCache(
    const Currency& currency,
    IBlockchainCache* parent,
    uint32_t startIndex) {

  return std::unique_ptr<IBlockchainCache>(new BlockchainCache(filename, currency, logger, parent, startIndex));
}

} //namespace CryptoNote
