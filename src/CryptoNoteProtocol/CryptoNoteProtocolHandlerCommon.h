// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <CryptoNoteProtocol/ICryptoNoteProtocolQuery.h>
#include <CryptoNote.h>

#include <vector>

namespace CryptoNote
{
  struct NOTIFY_NEW_BLOCK_request;

  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct ICryptoNoteProtocol {
    virtual void relayBlock(NOTIFY_NEW_BLOCK_request& arg) = 0;
    virtual void relayTransactions(const std::vector<BinaryArray>& transactions) = 0;
  };
  
  struct ICryptoNoteProtocolHandler : ICryptoNoteProtocol, public ICryptoNoteProtocolQuery {
  };
}
