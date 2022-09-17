// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <CryptoNoteCore/CryptoNoteSerialization.h>
#include <CryptoNoteCore/CryptoNoteTools.h>
#include <CryptoNoteCore/DatabaseCacheData.h>
#include <Serialization/SerializationOverloads.h>

namespace CryptoNote {

void ExtendedTransactionInfo::serialize(CryptoNote::ISerializer& s) {
  s(static_cast<CachedTransactionInfo&>(*this), "cached_transaction");
  s(amountToKeyIndexes, "key_indexes");
}

void KeyOutputInfo::serialize(ISerializer& s) {
  s(publicKey, "public_key");
  s(transactionHash, "transaction_hash");
  s(unlockTime, "unlock_time");
  s(outputIndex, "output_index");
}

}
