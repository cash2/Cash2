// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>

#include "CryptoNoteProtocol/ICryptoNoteProtocolObserver.h"
#include "CryptoNoteProtocol/ICryptoNoteProtocolQuery.h"
#include "CryptoNoteProtocol/CryptoNoteProtocolHandlerCommon.h"

class ICryptoNoteProtocolQueryStub : public CryptoNote::ICryptoNoteProtocolHandler {
public:
  ICryptoNoteProtocolQueryStub() : peers(0), observedHeight(0), synchronized(false) {
  }

  virtual bool addObserver(CryptoNote::ICryptoNoteProtocolObserver* observer) override;
  virtual bool removeObserver(CryptoNote::ICryptoNoteProtocolObserver* observer) override;
  virtual uint32_t getObservedHeight() const override;
  virtual size_t getPeerCount() const override;
  virtual bool isSynchronized() const override;

  void setPeerCount(uint32_t count);
  void setObservedHeight(uint32_t height);

  void setSynchronizedStatus(bool status);
  virtual void relayBlock(CryptoNote::NOTIFY_NEW_BLOCK_request& arg) override{};
  virtual void relayTransactions(const std::vector<CryptoNote::BinaryArray>& transactions) override{};


private:
  size_t peers;
  uint32_t observedHeight;

  bool synchronized;
};
