// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2018-2022 The Cash2 developers
//
// Please see the included LICENSE file for more information.
#pragma once

#include "IOutputStream.h"

#include <cstdint>
#include <vector>

namespace Common
{
    class VectorOutputStream : public IOutputStream
    {
      public:
        VectorOutputStream(std::vector<uint8_t> &out);

        VectorOutputStream &operator=(const VectorOutputStream &) = delete;

        uint64_t writeSome(const void *data, uint64_t size) override;

      private:
        std::vector<uint8_t> &out;
    };

} // namespace Common
