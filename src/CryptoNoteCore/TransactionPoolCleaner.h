// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "ITransactionPoolCleaner.h"

#include <chrono>
#include <unordered_map>

#include "crypto/crypto.h"

#include "CryptoNoteCore/ITimeProvider.h"
#include "ITransactionPool.h"
#include "Logging/ILogger.h"
#include "Logging/LoggerRef.h"

#include <System/ContextGroup.h>

namespace CryptoNote {

class TransactionPoolCleanWrapper: public ITransactionPoolCleanWrapper {
public:
  TransactionPoolCleanWrapper(
    std::unique_ptr<ITransactionPool>&& transactionPool,
    std::unique_ptr<ITimeProvider>&& timeProvider,
    Logging::ILogger& logger,
    uint64_t timeout);

  TransactionPoolCleanWrapper(const TransactionPoolCleanWrapper&) = delete;
  TransactionPoolCleanWrapper(TransactionPoolCleanWrapper&& other) = delete;

  TransactionPoolCleanWrapper& operator=(const TransactionPoolCleanWrapper&) = delete;
  TransactionPoolCleanWrapper& operator=(TransactionPoolCleanWrapper&&) = delete;

  virtual ~TransactionPoolCleanWrapper();

  virtual bool pushTransaction(CachedTransaction&& tx, TransactionValidatorState&& transactionState) override;
  virtual const CachedTransaction& getTransaction(const Crypto::Hash& hash) const override;
  virtual bool removeTransaction(const Crypto::Hash& hash) override;

  virtual size_t getTransactionCount() const override;
  virtual std::vector<Crypto::Hash> getTransactionHashes() const override;
  virtual bool checkIfTransactionPresent(const Crypto::Hash& hash) const override;

  virtual const TransactionValidatorState& getPoolTransactionValidationState() const override;
  virtual std::vector<CachedTransaction> getPoolTransactions() const override;

  virtual uint64_t getTransactionReceiveTime(const Crypto::Hash& hash) const override;
  virtual std::vector<Crypto::Hash> getTransactionHashesByPaymentId(const Crypto::Hash& paymentId) const override;

  virtual std::vector<Crypto::Hash> clean() override;

private:
  std::unique_ptr<ITransactionPool> transactionPool;
  std::unique_ptr<ITimeProvider> timeProvider;
  Logging::LoggerRef logger;
  std::unordered_map<Crypto::Hash, uint64_t> recentlyDeletedTransactions;
  uint64_t timeout;

  bool isTransactionRecentlyDeleted(const Crypto::Hash& hash) const;
  void cleanRecentlyDeletedTransactions(uint64_t currentTime);
};

} //namespace CryptoNote
