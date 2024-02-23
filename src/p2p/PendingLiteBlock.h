// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2018-2022 The Cash2 developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include "cryptonoteprotocol/CryptoNoteProtocolDefinitions.h"

#include <unordered_set>

namespace CryptoNote
{
    struct PendingLiteBlock
    {
        NOTIFY_NEW_LITE_BLOCK_request request;
        std::unordered_set<Crypto::Hash> missed_transactions;
    };
} // namespace CryptoNote
