#include <cstdint>
#include <format>
#include <iostream>
#include <random>
#include <string>

uint64_t b_trial(float p, float random_float) { return p > random_float; }

int main(int argc, char *argv[]) {
  // Probability p from command line. Trials.
  double p = std::stof(argv[1]);
  uint64_t n = 0xFFFFFF;

  std::random_device rd;
  std::mt19937_64 m_rng(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  uint64_t trials_sum = 0;

  for (int j = 0; j < n * 4; ++j) {
    float random_float = dis(m_rng);
    trials_sum += b_trial(p, random_float);
  }

  std::cout << std::format("Observed p = {}",
                           trials_sum / static_cast<float>(n * 4));
  return 0;
}
