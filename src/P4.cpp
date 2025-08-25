#include "xoshiro128plus.h"
#include <cstdint>
#include <format>
#include <immintrin.h>
#include <iostream>
#include <random>
#include <string>

__m256i b_trial(const __m256d p, const __m256d X, const __m256i ones) {
  // Bernouilli trial. Compare p with a random number X in [0, 1):
  //                 { 1 if p > X
  // b_trial(p, X) = {
  //                 { 0 if p <= X
  //
  // Using SIMD (AVX2) since this task is highly parallelizable.
  // What _mm256_cmp_pd does is compare two vectors of doubles and return
  // vectors of 1 or 0 depending on whether the comparison is true or false.
  // Then __mm256_and_si256 returns a simple count of how many 1s and 0s are in
  // the vector returned by cmp_pd
  __m256d trial_results_d = _mm256_cmp_pd(X, p, _CMP_LT_OQ);
  __m256i trial_results = _mm256_castpd_si256(trial_results_d);
  trial_results = _mm256_and_si256(trial_results, ones);

  return trial_results;
}

uint64_t extract_trials_sum(const __m256i &);

int main(int argc, char *argv[]) {
  // Get p from command line. Run 0xFFFFFF * 4 trials.
  double p = std::stof(argv[1]);
  uint64_t n = 0xFFFFFF;
  // Fill a 4*64 = 256 bit vector with p.
  __m256d p_v = _mm256_set1_pd(p);

  // Initialize random number generator to seed the xoshiro128+ RNG.
  // Set up xorshift128+ RNG with a random number from C++ std::random's
  // Mersenne Twister RNG. Although not cryptographically secure, it has enough
  // randomness and a large enough period that it suffices for this program.
  std::random_device rd;
  std::mt19937_64 m_rng(rd());
  Xoshiro128P_RNG x128_RNG(m_rng);

  // 4 x 64 = 256 bit vectors that will hold the sum of trials and a bitmask for
  // the b_trial(p, X) function comparison.
  __m256i trials_sum = _mm256_setzero_si256();
  __m256i ones_int = _mm256_set1_epi64x(1);

  for (int j = 0; j < n; ++j) {
    // Four random numbers.
    __m256d X = x128_RNG.generate_random_db();
    // Equivalent to trials_sum += trials_sum + b_trial(p, X)
    // Just vectorized with SIMD.
    trials_sum = _mm256_add_epi64(trials_sum, b_trial(p_v, X, ones_int));
  }

  // Sum all the trials in the accumulator vector trials_sum.
  uint64_t trials_sum_int = extract_trials_sum(trials_sum);

  // Finally! Divide the sum of successful trials by the number of trials to
  // obtain an observed p, which, due to very large number of trials
  // (~268.4 million!!) should be very close to the entered p.
  double observed_p = trials_sum_int / static_cast<float>(n * 4);
  std::cout << std::format("Observed p = {:.7f}\n.", observed_p);
  std::cout << std::format("{0}p = {1:.7f}.\n", "Δ", p - observed_p);
  return 0;
}

uint64_t extract_trials_sum(const __m256i &trials_sum) {
  // Extract and sum the upper and lower halves of a 4 x 64 = 256 bit vector
  // into a 2 x 64 = 128 bit vector. Repeat with the 128 bit vector to reduce to
  // a 64 bit unsigned integer. This is the final sum of trials.
  __m128i trial_sum_128 = _mm_add_epi64(_mm256_extracti128_si256(trials_sum, 1),
                                        _mm256_castsi256_si128(trials_sum));
  return _mm_extract_epi64(trial_sum_128, 1) + _mm_cvtsi128_si64(trial_sum_128);
}
