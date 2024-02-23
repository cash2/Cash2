// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2018-2022 The Cash2 developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include <cstdint>

namespace Common
{
    namespace Console
    {
        enum class Color : uint8_t
        {
            Default,

            Blue,
            Green,
            Red,
            Yellow,
            White,
            Cyan,
            Magenta,

            BrightBlue,
            BrightGreen,
            BrightRed,
            BrightYellow,
            BrightWhite,
            BrightCyan,
            BrightMagenta
        };

        void setTextColor(Color color);

        bool isConsoleTty();

    } // namespace Console
} // namespace Common
