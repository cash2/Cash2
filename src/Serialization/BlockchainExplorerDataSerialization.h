// Copyright (c) 2011-2017 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "BlockchainExplorerData.h"

#include "Serialization/ISerializer.h"

namespace CryptoNote {

void serialize(TransactionOutputDetails& output, ISerializer& serializer);
void serialize(TransactionOutputReferenceDetails& outputReference, ISerializer& serializer);

void serialize(BaseInputDetails& inputBase, ISerializer& serializer);
void serialize(KeyInputDetails& inputToKey, ISerializer& serializer);
void serialize(TransactionInputDetails& input, ISerializer& serializer);

void serialize(TransactionExtraDetails& extra, ISerializer& serializer);
void serialize(TransactionDetails& transaction, ISerializer& serializer);

void serialize(BlockDetails& block, ISerializer& serializer);

} //namespace CryptoNote
