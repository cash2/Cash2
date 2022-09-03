// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "CryptoNoteCore/CryptoNoteBasic.h"
#include "CryptoNoteCore/Difficulty.h"

namespace CryptoNote {
  struct IMinerHandler {
    virtual bool handle_block_found(BlockTemplate& b) = 0;
    virtual bool get_block_template(BlockTemplate& b, const AccountPublicAddress& adr, Difficulty& diffic, uint32_t& blockchainHeight, const BinaryArray& ex_nonce) = 0;

  protected:
    ~IMinerHandler(){};
  };
}
