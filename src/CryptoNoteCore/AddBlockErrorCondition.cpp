// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "AddBlockErrorCondition.h"

namespace CryptoNote {
namespace error {

AddBlockErrorConditionCategory AddBlockErrorConditionCategory::INSTANCE;


std::error_condition make_error_condition(AddBlockErrorCondition e) {
  return std::error_condition(
      static_cast<int>(e),
      AddBlockErrorConditionCategory::INSTANCE);
}

}
}
