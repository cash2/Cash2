// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018 The Turtlecoin developers
// Copyright (c) 2016-2019, The Karbo Developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <string>
#include <stdexcept>
#include <cstdint>

#include <boost/program_options.hpp>

namespace PaymentService {

class ConfigurationError : public std::runtime_error {
public:
  ConfigurationError(const char* desc) : std::runtime_error(desc) {}
};

struct Configuration {
  Configuration();

  void init(const boost::program_options::variables_map& options);
  static void initOptions(boost::program_options::options_description& desc);

  std::string bindAddress;
  uint16_t bindPort;
  std::string rpcConfigurationPassword;

  std::string containerFile;
  std::string containerPassword;
  std::string logFile;
  std::string serverRoot;
  std::string spendPrivateKey;
  std::string viewPrivateKey;

  bool generateNewContainer;
  bool daemonize;
  bool registerService;
  bool unregisterService;
  bool testnet;
  bool printAddresses;

  size_t logLevel;
};

} //namespace PaymentService
