// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2018-2022 The Cash2 developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include "IInputStream.h"

namespace Common
{
    class MemoryInputStream : public IInputStream
    {
      public:
        MemoryInputStream(const void *buffer, uint64_t bufferSize);

        bool endOfStream() const;

        // IInputStream
        virtual uint64_t readSome(void *data, uint64_t size) override;

      private:
        const char *buffer;

        uint64_t bufferSize;

        uint64_t position;
    };
} // namespace Common
