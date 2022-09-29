// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "DataBaseMock.h"

using namespace CryptoNote;

DataBaseMock::~DataBaseMock() {

}

std::error_code DataBaseMock::write(IWriteBatch& batch) {
  auto append = batch.extractRawDataToInsert();
  for (auto pr : append) {
    baseState[pr.first] = pr.second;
  }
  auto remove = batch.extractRawKeysToRemove();
  for (auto key : remove) {
    baseState.erase(key);
  }
  return{};
}

std::error_code DataBaseMock::writeSync(IWriteBatch& batch) {
  return write(batch);
}

std::error_code DataBaseMock::read(IReadBatch& batch) {
  auto keys = batch.getRawKeys();
  std::vector<std::string> kvs;
  std::vector<bool> states;
  for (auto key : keys) {
    auto it = baseState.find(key);
    if (it != baseState.end()) {
      kvs.push_back(it->second);
      states.push_back(true);
    } else {
      kvs.push_back("");
      states.push_back(false);
    }
  }

  batch.submitRawResult(kvs, states);
  return{};
}

std::unordered_map<uint32_t, RawBlock> DataBaseMock::blocks() {
  BlockchainReadBatch req;
  for (int i = 0; i < 30; ++i) {
    req.requestRawBlock(i);
  }
  read(req);
  auto result = req.extractResult();
  return result.getRawBlocks();
}
