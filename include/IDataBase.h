// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <string>
#include <system_error>

#include "IWriteBatch.h"
#include "IReadBatch.h"

namespace CryptoNote {

class IDataBase {
public:
  virtual ~IDataBase() {
  }

  virtual std::error_code write(IWriteBatch& batch) = 0;
  virtual std::error_code writeSync(IWriteBatch& batch) = 0;

  virtual std::error_code read(IReadBatch& batch) = 0;
};
}
