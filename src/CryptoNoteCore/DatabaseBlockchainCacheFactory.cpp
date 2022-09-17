// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "DatabaseBlockchainCacheFactory.h"

#include "IDataBase.h"

#include "BlockchainCache.h"
#include "DatabaseBlockchainCache.h"

namespace CryptoNote {

DatabaseBlockchainCacheFactory::DatabaseBlockchainCacheFactory(IDataBase& database, Logging::ILogger& logger): database(database), logger(logger) {

}

DatabaseBlockchainCacheFactory::~DatabaseBlockchainCacheFactory() {

}

std::unique_ptr<IBlockchainCache> DatabaseBlockchainCacheFactory::createRootBlockchainCache(const Currency& currency) {
  return std::unique_ptr<IBlockchainCache> (new DatabaseBlockchainCache(currency, database, *this, logger));
}

std::unique_ptr<IBlockchainCache> DatabaseBlockchainCacheFactory::createBlockchainCache(const Currency& currency, IBlockchainCache* parent, uint32_t startIndex) {
  return std::unique_ptr<IBlockchainCache> (new BlockchainCache("", currency, logger, parent, startIndex));
}

} //namespace CryptoNote
