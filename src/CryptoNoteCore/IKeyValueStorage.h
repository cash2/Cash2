// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <vector>

namespace CryptoNote {

class WriteBatch;
class ReadBatch;

class IKeyValueStorage {
public:
  virtual ~IKeyValueStorage() {
  }

  virtual bool insert(const WriteBatch& batch, bool sync = false) = 0;
  virtual void read(const ReadBatch& batch) const = 0;
};
}
