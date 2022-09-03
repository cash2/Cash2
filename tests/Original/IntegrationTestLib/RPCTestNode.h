// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <stdint.h>
#include <System/Dispatcher.h>
#include "HTTP/HttpRequest.h"
#include "HTTP/HttpResponse.h"
#include "Logging/ConsoleLogger.h"
#include "Logging/LoggerRef.h"
#include "Rpc/HttpClient.h"

#include "TestNode.h"

using namespace CryptoNote;

namespace Tests {
  class RPCTestNode : public TestNode {
  public:
    RPCTestNode(uint16_t port, System::Dispatcher& d);

    virtual bool startMining(size_t threadsCount, const std::string& address) override;
    virtual bool stopMining() override;
    virtual bool stopDaemon() override;
    virtual bool getBlockTemplate(const std::string& minerAddress, CryptoNote::BlockTemplate& blockTemplate, uint64_t& difficulty) override;
    virtual bool submitBlock(const std::string& block) override;
    virtual bool getTailBlockId(Crypto::Hash& tailBlockId) override;
    virtual bool makeINode(std::unique_ptr<CryptoNote::INode>& node) override;
    virtual uint64_t getLocalHeight() override;

    virtual ~RPCTestNode() { }

  private:
    Logging::ConsoleLogger m_log;
    Logging::LoggerRef m_logger;
    uint16_t m_rpcPort;
    System::Dispatcher& m_dispatcher;
    CryptoNote::HttpClient m_httpClient;
  };
}
