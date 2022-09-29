// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <unordered_map>
#include <map>

#include <IDataBase.h>
#include "CryptoNoteCore/BlockchainReadBatch.h"
#include "CryptoNoteCore/BlockchainWriteBatch.h"

namespace CryptoNote {

class DataBaseMock : public IDataBase {
public:
  DataBaseMock() = default;
  ~DataBaseMock() override;

  std::error_code write(IWriteBatch& batch) override;
  std::error_code writeSync(IWriteBatch& batch) override;
  std::error_code read(IReadBatch& batch) override;
  std::unordered_map<uint32_t, RawBlock> blocks();

  std::map<std::string, std::string> baseState;
};
}
