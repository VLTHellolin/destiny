#pragma once

#include <concepts>
#include <cstdint>

namespace destiny {

template <typename Tp>
concept HasTimesOperator = requires(Tp a, Tp b) {
  { a * b } -> std::convertible_to<Tp>;
  { a *= b } -> std::convertible_to<Tp>;
};

template <HasTimesOperator Tp>
constexpr Tp pow(Tp x, uint64_t exp) {
  Tp res {1};
  for (; exp != 0; exp /= 2) {
    if (exp & 1) {
      res *= x;
    }
    x *= x;
  }
  return res;
}

template <HasTimesOperator Tp>
constexpr Tp pow(Tp x, uint64_t exp, Tp mod) {
  Tp res {1};
  for (; exp != 0; exp /= 2) {
    if (exp & 1) {
      res = (res * x) % mod;
    }
    x = (x * x) % mod;
  }
  return res;
}

}
