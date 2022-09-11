// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <vector>
#include <boost/variant.hpp>
#include "CryptoTypes.h"

namespace CryptoNote {

struct BaseInput {
  uint32_t blockIndex;
};

struct KeyInput {
  uint64_t amount;
  std::vector<uint32_t> outputIndexes;
  Crypto::KeyImage keyImage;
};

struct KeyOutput {
  Crypto::PublicKey key;
};

typedef boost::variant<BaseInput, KeyInput> TransactionInput;

typedef boost::variant<KeyOutput> TransactionOutputTarget;

struct TransactionOutput {
  uint64_t amount;
  TransactionOutputTarget target;
};

struct TransactionPrefix {
  uint8_t version;
  uint64_t unlockTime;
  std::vector<TransactionInput> inputs;
  std::vector<TransactionOutput> outputs;
  std::vector<uint8_t> extra;
};

struct Transaction : public TransactionPrefix {
  std::vector<std::vector<Crypto::Signature>> signatures;
};

struct BaseTransaction : public TransactionPrefix {
};

struct ParentBlock {
  uint8_t majorVersion;
  uint8_t minorVersion;
  Crypto::Hash previousBlockHash;
  uint16_t transactionCount;
  std::vector<Crypto::Hash> baseTransactionBranch;
  BaseTransaction baseTransaction;
  std::vector<Crypto::Hash> blockchainBranch;
};

struct BlockHeader {
  uint8_t majorVersion;
  uint8_t minorVersion;
  uint32_t nonce;
  uint64_t timestamp;
  Crypto::Hash previousBlockHash;
  Crypto::Hash merkleRoot;
};

struct BlockTemplate : public BlockHeader {
  ParentBlock parentBlock;
  Transaction baseTransaction;
  std::vector<Crypto::Hash> transactionHashes;
};

struct AccountPublicAddress {
  Crypto::PublicKey spendPublicKey;
  Crypto::PublicKey viewPublicKey;
};

struct AccountKeys {
  AccountPublicAddress address;
  Crypto::SecretKey spendSecretKey;
  Crypto::SecretKey viewSecretKey;
};

struct KeyPair {
  Crypto::PublicKey publicKey;
  Crypto::SecretKey secretKey;
};

using BinaryArray = std::vector<uint8_t>;

struct RawBlock {
  BinaryArray block; //BlockTemplate
  std::vector<BinaryArray> transactions;
};

}
