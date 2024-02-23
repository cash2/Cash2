// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2018-2022 The Cash2 developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include "CachedTransaction.h"
#include "CryptoNote.h"
#include "common/CryptoNoteTools.h"

#include <vector>

namespace CryptoNote
{
    namespace Utils
    {
        bool restoreCachedTransactions(
            const std::vector<BinaryArray> &binaryTransactions,
            std::vector<CachedTransaction> &transactions);

    } // namespace Utils
} // namespace CryptoNote
