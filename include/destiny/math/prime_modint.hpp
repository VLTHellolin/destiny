#pragma once

#include <concepts>
#include <cstdint>
#include <type_traits>

#include "pow.hpp"

namespace destiny {

template <uint64_t Mod>
struct PrimeModInt {
  using intTp = uint64_t;
  using intSignedTp = std::make_signed_t<intTp>;
  using mint = PrimeModInt<Mod>;

  static constexpr intTp intCapSqrt = 4294967295;
  static constexpr bool safeMul = Mod <= intCapSqrt;

  constexpr intTp value() const { return val; }
  static constexpr uint64_t mod() { return Mod; }

  constexpr PrimeModInt() = default;
  constexpr PrimeModInt(std::unsigned_integral auto init) {
    val = init % Mod;
  }
  constexpr PrimeModInt(std::signed_integral auto init) {
    intSignedTp tmp = init % static_cast<intSignedTp>(Mod);
    if (tmp < 0) {
      tmp += Mod;
    }
    val = static_cast<intTp>(tmp);
  }

  static constexpr mint from(intTp x) {
    mint res;
    res.val = x;
    return res;
  }

  constexpr mint inv() const { return from(pow(val, Mod - 2, Mod)); }

  constexpr mint operator+() const { return *this; }
  constexpr mint operator-() const {
    if (val == 0) {
      return *this;
    } else {
      return from(Mod - val);
    }
  }

  constexpr mint &operator++() {
    if (val == Mod - 1) {
      val = 0;
    } else {
      ++val;
    }
    return *this;
  }
  constexpr mint operator++(int) {
    mint res = *this;
    ++*this;
    return res;
  }
  constexpr mint &operator--() {
    if (val == 0) {
      val = Mod - 1;
    } else {
      --val;
    }
    return *this;
  }
  constexpr mint operator--(int) {
    mint res = *this;
    --*this;
    return res;
  }

  constexpr mint &operator+=(const mint &rhs) {
    val += rhs.val;
    if (val >= Mod) {
      val -= Mod;
    }
    return *this;
  }
  constexpr mint &operator-=(const mint &rhs) {
    val += Mod - rhs.val;
    if (val >= Mod) {
      val -= Mod;
    }
    return *this;
  }
  constexpr mint &operator*=(const mint &rhs) {
    if constexpr (safeMul) {
      val = (val * rhs.val) % Mod;
    } else {
      val = (static_cast<__uint128_t>(val) * rhs.val) % static_cast<__uint128_t>(Mod);
    }
    return *this;
  }
  constexpr mint &operator/=(const mint &rhs) { return *this *= rhs.inv(); }
  friend constexpr mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
  friend constexpr mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
  friend constexpr mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
  friend constexpr mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }

  friend constexpr auto operator<=>(const mint &, const mint &) = default;

private:
  intTp val {};
};

}
