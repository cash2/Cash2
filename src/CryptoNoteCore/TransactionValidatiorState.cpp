// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "TransactionValidatiorState.h"

namespace CryptoNote {

void mergeStates(TransactionValidatorState& destionation, const TransactionValidatorState& source) {
  destionation.spentKeyImages.insert(source.spentKeyImages.begin(), source.spentKeyImages.end());
}

bool hasIntersections(const TransactionValidatorState& destination, const TransactionValidatorState& source) {
  return std::any_of(source.spentKeyImages.begin(), source.spentKeyImages.end(),
                     [&](const Crypto::KeyImage& ki) { return destination.spentKeyImages.count(ki) != 0; });
}

void excludeFromState(TransactionValidatorState& state, const CachedTransaction& cachedTransaction) {
  const auto& transaction = cachedTransaction.getTransaction();
  for (auto& input : transaction.inputs) {
    if (input.type() == typeid(KeyInput)) {
      const auto& in = boost::get<KeyInput>(input);
      assert(state.spentKeyImages.count(in.keyImage) > 0);
      state.spentKeyImages.erase(in.keyImage);
    } else {
      assert(false);
    }
  }
}

}
