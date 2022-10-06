// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2014-2018, The Monero Project
// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2018-2019, The Karbo Developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <crypto/random.h>

#include <unordered_map>

class SequenceEnded: public std::runtime_error {
public:
  SequenceEnded() : std::runtime_error("shuffle sequence ended") {
  }

  ~SequenceEnded(){}
};

template <typename T>
class ShuffleGenerator {
public:

  ShuffleGenerator(T n) :
    N(n), count(n) {}

  T operator()() {

    if (count == 0) {
      throw SequenceEnded();
    }

    T value = Random::randomValue<T>(0, --count);

    auto rvalIt = selected.find(count);
    auto rval = rvalIt != selected.end() ? rvalIt->second : count;

    auto lvalIt = selected.find(value);

    if (lvalIt != selected.end()) {
      value = lvalIt->second;
      lvalIt->second = rval;
    } else {
      selected[value] = rval;
    }

    return value;
  }

  bool empty() const {
    return count == 0;
  }

  void reset() {
    count = N;
    selected.clear();
  }

private:

  std::unordered_map<T, T> selected;
  T count;
  const T N;
};
