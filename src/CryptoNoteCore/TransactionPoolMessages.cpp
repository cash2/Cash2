// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <CryptoNoteCore/TransactionPoolMessages.h>

namespace CryptoNote {

TransactionPoolMessage::TransactionPoolMessage(const AddTransaction& at)
    : type(TransactionMessageType::AddTransactionType), addTransaction(at) {
}

TransactionPoolMessage::TransactionPoolMessage(const DeleteTransaction& dt)
    : type(TransactionMessageType::DeleteTransactionType), deleteTransaction(dt) {
}

// pattern match
void TransactionPoolMessage::match(std::function<void(const AddTransaction&)>&& addTxVisitor,
                                   std::function<void(const DeleteTransaction&)>&& delTxVisitor) {
  switch (getType()) {
    case TransactionMessageType::AddTransactionType:
      addTxVisitor(addTransaction);
      break;
    case TransactionMessageType::DeleteTransactionType:
      delTxVisitor(deleteTransaction);
      break;
  }
}

// API with explicit type handling
TransactionMessageType TransactionPoolMessage::getType() const {
  return type;
}

AddTransaction TransactionPoolMessage::getAddTransaction() const {
  assert(getType() == TransactionMessageType::AddTransactionType);
  return addTransaction;
}

DeleteTransaction TransactionPoolMessage::getDeleteTransaction() const {
  assert(getType() == TransactionMessageType::DeleteTransactionType);
  return deleteTransaction;
}

TransactionPoolMessage makeAddTransaction(const Crypto::Hash& hash) {
  return TransactionPoolMessage{AddTransaction{hash}};
}

TransactionPoolMessage makeDelTransaction(const Crypto::Hash& hash) {
  return TransactionPoolMessage{DeleteTransaction{hash}};
}
}
