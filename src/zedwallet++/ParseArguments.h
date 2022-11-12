// Copyright (c) 2018-2019, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include <config/CryptoNoteConfig.h>
#include <logger/Logger.h>
#include <optional>

struct ZedConfig
{
    /* Was the wallet file specified on CLI */
    bool walletGiven = false;

    /* Was the wallet pass specified on CLI */
    bool passGiven = false;

    /* Was the reset arg specified on CLI */
    bool resetGiven = false;

    /* The daemon host */
    std::string host;

    /* The daemon port */
    uint16_t port = CryptoNote::RPC_DEFAULT_PORT;

    /* The wallet file path */
    std::string walletFile;

    /* The wallet password */
    std::string walletPass;

    /* The reset block height */
    uint64_t resetFromHeight;

    /* Controls what level of messages to log */
    Logger::LogLevel logLevel = Logger::FATAL;

    /* Optionally log to a file */
    std::optional<std::string> loggingFilePath;

    /* Use SSL with daemon */
    bool ssl = false;

    unsigned int threads;
};

ZedConfig parseArguments(int argc, char **argv);
