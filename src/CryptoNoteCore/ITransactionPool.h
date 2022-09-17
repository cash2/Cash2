// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once
#include "CachedTransaction.h"

namespace CryptoNote {

struct TransactionValidatorState;

class ITransactionPool {
public:
  virtual bool pushTransaction(CachedTransaction&& tx, TransactionValidatorState&& transactionState) = 0;
  virtual const CachedTransaction& getTransaction(const Crypto::Hash& hash) const = 0;
  virtual bool removeTransaction(const Crypto::Hash& hash) = 0;

  virtual size_t getTransactionCount() const = 0;
  virtual std::vector<Crypto::Hash> getTransactionHashes() const = 0;
  virtual bool checkIfTransactionPresent(const Crypto::Hash& hash) const = 0;

  virtual const TransactionValidatorState& getPoolTransactionValidationState() const = 0;
  virtual std::vector<CachedTransaction> getPoolTransactions() const = 0;

  virtual uint64_t getTransactionReceiveTime(const Crypto::Hash& hash) const = 0;
  virtual std::vector<Crypto::Hash> getTransactionHashesByPaymentId(const Crypto::Hash& paymentId) const = 0;
};

}
