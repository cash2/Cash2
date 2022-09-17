// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "IBlockchainCacheFactory.h"
#include <Logging/LoggerMessage.h>

namespace CryptoNote {

class IDataBase;

class DatabaseBlockchainCacheFactory: public IBlockchainCacheFactory {
public:
  explicit DatabaseBlockchainCacheFactory(IDataBase& database, Logging::ILogger& logger);
  virtual ~DatabaseBlockchainCacheFactory();

  virtual std::unique_ptr<IBlockchainCache> createRootBlockchainCache(const Currency& currency) override;
  virtual std::unique_ptr<IBlockchainCache> createBlockchainCache(const Currency& currency, IBlockchainCache* parent, uint32_t startIndex = 0) override;

private:
  IDataBase& database;
  Logging::ILogger& logger;
};

} //namespace CryptoNote
