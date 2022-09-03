// Copyright (c) 2011-2016 The Cryptonote developers, The Bytecoin developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <string>

#include "IWallet.h"
#include "CryptoNoteCore/Currency.h"
#include "Wallet/WalletGreen.h"

namespace CryptoNote {

void throwIfKeysMismatch(const Crypto::SecretKey& secretKey, const Crypto::PublicKey& expectedPublicKey, const std::string& message = "");
bool validateAddress(const std::string& address, const CryptoNote::Currency& currency);

std::ostream& operator<<(std::ostream& os, CryptoNote::WalletTransactionState state);
std::ostream& operator<<(std::ostream& os, CryptoNote::WalletTransferType type);
std::ostream& operator<<(std::ostream& os, CryptoNote::WalletGreen::WalletState state);
std::ostream& operator<<(std::ostream& os, CryptoNote::WalletGreen::WalletTrackingMode mode);

class TransferListFormatter {
public:
  explicit TransferListFormatter(const CryptoNote::Currency& currency, const WalletGreen::TransfersRange& range);

  void print(std::ostream& os) const;

  friend std::ostream& operator<<(std::ostream& os, const TransferListFormatter& formatter);

private:
  const CryptoNote::Currency& m_currency;
  const WalletGreen::TransfersRange& m_range;
};

class WalletOrderListFormatter {
public:
  explicit WalletOrderListFormatter(const CryptoNote::Currency& currency, const std::vector<CryptoNote::WalletOrder>& walletOrderList);

  void print(std::ostream& os) const;

  friend std::ostream& operator<<(std::ostream& os, const WalletOrderListFormatter& formatter);

private:
  const CryptoNote::Currency& m_currency;
  const std::vector<CryptoNote::WalletOrder>& m_walletOrderList;
};

}
