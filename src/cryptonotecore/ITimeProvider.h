// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2018-2022 The Cash2 developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include <time.h>

namespace CryptoNote
{
    struct ITimeProvider
    {
        virtual time_t now() = 0;

        virtual ~ITimeProvider() {}
    };

    struct RealTimeProvider : public ITimeProvider
    {
        virtual time_t now() override
        {
            return time(nullptr);
        }
    };

} // namespace CryptoNote
