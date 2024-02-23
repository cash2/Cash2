// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2018-2022 The Cash2 developers
//
// Please see the included LICENSE file for more information.

#include "StringOutputStream.h"

namespace Common
{
    StringOutputStream::StringOutputStream(std::string &out): out(out) {}

    uint64_t StringOutputStream::writeSome(const void *data, uint64_t size)
    {
        out.append(static_cast<const char *>(data), size);
        return size;
    }

} // namespace Common
