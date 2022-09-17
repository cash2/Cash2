// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <atomic>
#include <memory>
#include <string>

#include "rocksdb/db.h"

#include "IDataBase.h"
#include "DataBaseConfig.h"

#include <Logging/LoggerRef.h>

namespace CryptoNote {

class RocksDBWrapper : public IDataBase {
public:
  RocksDBWrapper(Logging::ILogger& logger);
  virtual ~RocksDBWrapper();

  RocksDBWrapper(const RocksDBWrapper&) = delete;
  RocksDBWrapper(RocksDBWrapper&&) = delete;

  RocksDBWrapper& operator=(const RocksDBWrapper&) = delete;
  RocksDBWrapper& operator=(RocksDBWrapper&&) = delete;

  void init(const DataBaseConfig& config);
  void shutdown();
  void destoy(const DataBaseConfig& config); //Be careful with this method!

  std::error_code write(IWriteBatch& batch) override;
  std::error_code writeSync(IWriteBatch& batch) override;
  std::error_code read(IReadBatch& batch) override;

private:
  std::error_code write(IWriteBatch& batch, bool sync);

  rocksdb::Options getDBOptions(const DataBaseConfig& config);
  std::string getDataDir(const DataBaseConfig& config);

  enum State {
    NOT_INITIALIZED,
    INITIALIZED
  };

  Logging::LoggerRef logger;
  std::unique_ptr<rocksdb::DB> db;
  std::atomic<State> state;
};
}
