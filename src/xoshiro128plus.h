//	Parallel implementation of xoshiro128+ RNG.
//	Most code written originally by stackoverflow user o9000
//	(https://stackoverflow.com/users/5404527/o9000) @
//	https://stackoverflow.com/questions/24001930/avx-sse-version-of-xorshift128
//	Which in turn is a scalar version found at
//	http://vigna.di.unimi.it/ftp/papers/xorshiftplus.pdf
//  By Sebastiano Vigna (2017).

#pragma once

#include <cstdint>
#include <immintrin.h>
#include <random>

class Xoshiro128P_RNG {
public:
  // Initialize states.
  explicit Xoshiro128P_RNG(std::mt19937_64 &m_rng);

  // Return four random doubles.
  __m256d generate_random_db();

private:
  __m256i generate_random_ints();
  __m256d normalize_ints_to_floats(__m256i random_ints);

  // State vectors.
  __m256i m_state0;
  __m256i m_state1;

  const __m256i m_exponent_mask;
  const __m256d m_ones;
};
