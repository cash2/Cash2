// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstddef>

namespace CryptoNote {

class ICryptoNoteProtocolObserver {
public:
  virtual void peerCountUpdated(size_t count) {}
  virtual void lastKnownBlockHeightUpdated(uint32_t height) {}
  virtual void blockchainSynchronized(uint32_t topHeight) {}
};

} //namespace CryptoNote
