#pragma once

#include <chrono>
#include <cstdint>
#include <random>

namespace destiny {

namespace _randomImpl {

struct Seed {
  uint64_t val;
  Seed() {
    val = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    val = splitmix64(val);
  }

private:
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
};

static const uint64_t FIXED_RANDOM = Seed().val;
static std::mt19937_64 RANDOM_ENGINE {FIXED_RANDOM};

}

uint32_t rand32() {
  return _randomImpl::RANDOM_ENGINE();
}

uint64_t rand64() {
  return _randomImpl::RANDOM_ENGINE();
}

int64_t rand64(int64_t l, int64_t r) {
  std::uniform_int_distribution<int64_t> dist(l, r);
  return dist(_randomImpl::RANDOM_ENGINE);
}

template <std::random_access_iterator Tp>
void shuffle(Tp first, Tp last) {
  std::shuffle(first, last, _randomImpl::RANDOM_ENGINE);
}

void shuffle(auto &&r) {
  shuffle(std::begin(r), std::end(r));
}

}
