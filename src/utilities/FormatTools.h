// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2014-2018, The Monero Project
// Copyright (c) 2018-2020, The TurtleCoin Developers
// Copyright (c) 2018-2022 The Cash2 developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include <string>
#include <vector>

namespace Utilities
{
    enum ForkStatus
    {
        UpToDate,
        ForkLater,
        ForkSoonReady,
        ForkSoonNotReady,
        OutOfDate
    };

    ForkStatus get_fork_status(
        const uint64_t height,
        const std::vector<uint64_t> upgrade_heights,
        const uint64_t supported_height);

    std::string get_upgrade_info(const uint64_t supported_height, const std::vector<uint64_t> upgrade_heights);

    std::string get_update_status(const ForkStatus forkStatus);

    std::string get_fork_time(const uint64_t height, const std::vector<uint64_t> upgrade_heights);

    std::string get_mining_speed(const uint64_t hashrate);

    std::string get_sync_percentage(uint64_t height, const uint64_t target_height);

    std::string get_upgrade_time(const uint64_t height, const uint64_t upgrade_height);

    std::string formatAmount(const uint64_t amount);

    std::string formatAmountBasic(const uint64_t amount);

    std::string prettyPrintBytes(const uint64_t numBytes);

    std::string unixTimeToDate(const uint64_t timestamp);
} // namespace Utilities
