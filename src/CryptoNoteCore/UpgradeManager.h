// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "IUpgradeManager.h"

#include <memory>

#include "IUpgradeDetector.h"

namespace CryptoNote {

//Simple upgrade manager version. It doesn't support voting for now.
class UpgradeManager: public IUpgradeManager {
public:
  UpgradeManager();
  virtual ~UpgradeManager();

  virtual void addMajorBlockVersion(uint8_t targetVersion, uint32_t upgradeHeight) override;

  virtual uint8_t getBlockMajorVersion(uint32_t blockIndex) const override;

private:
  std::vector<std::unique_ptr<IUpgradeDetector>> m_upgradeDetectors;
};

} //namespace CryptoNote
