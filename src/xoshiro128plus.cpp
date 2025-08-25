//	Parallel implementation of xoshiro128+ RNG.
//	Most code written originally by stackoverflow user o9000
//	(https://stackoverflow.com/users/5404527/o9000) @
//	https://stackoverflow.com/questions/24001930/avx-sse-version-of-xorshift128
//	Which in turn is a scalar version found at
//	http://vigna.di.unimi.it/ftp/papers/xorshiftplus.pdf
//  By Sebastiano Vigna (2017).
//  This is to say, few of this code is mine and this was just an exercise in
//  learning C++ SIMD by adapting algorithms and implementations by others.

#include "xoshiro128plus.h"

Xoshiro128P_RNG::Xoshiro128P_RNG(std::mt19937_64 &m_rng)
    : // Initialize state 2 * (256 bit vectors). Exponent mask and ones for
      // normalizing random ints into doubles in the interval [0, 1).
      m_state0(_mm256_set_epi64x(m_rng(), m_rng(), m_rng(), m_rng())),
      m_state1(_mm256_set_epi64x(m_rng(), m_rng(), m_rng(), m_rng())),
      m_exponent_mask(_mm256_set1_epi64x(0x3FF0000000000000ULL)),
      m_ones(_mm256_set1_pd(1.0)) {}

__m256i Xoshiro128P_RNG::generate_random_ints() {
  __m256i s1 = m_state0;
  const __m256i s0 = m_state1;
  m_state0 = s0;
  s1 = _mm256_xor_si256(s1, _mm256_slli_epi64(s1, 23));
  m_state1 = _mm256_xor_si256(
      _mm256_xor_si256(_mm256_xor_si256(s1, s0), _mm256_srli_epi64(s1, 18)),
      _mm256_srli_epi64(s0, 5));
  return _mm256_add_epi64(m_state1, s0);
}

__m256d Xoshiro128P_RNG::normalize_ints_to_floats(__m256i random_ints) {
  __m256i top_52_bits = _mm256_srli_epi64(random_ints, 12);
  __m256i double_bits = _mm256_or_si256(top_52_bits, m_exponent_mask);
  __m256d doubles_in_range_1_to_2 = _mm256_castsi256_pd(double_bits);
  return _mm256_sub_pd(doubles_in_range_1_to_2, m_ones);
}

__m256d Xoshiro128P_RNG::generate_random_db() {
  return normalize_ints_to_floats(generate_random_ints());
}
