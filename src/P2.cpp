#include <format>
#include <iostream>
#include <string>

void get_user_input(auto &k, std::string k_char);
float pow_recursive(auto k, uint n) {
  // We pass a float k and unsigned (positive) int n to this function.
  // Then if n >= 1 we subtract 1 from n and then pass that and k to the
  // function again, and multiply that by k.
  // Then if n == 0 we return 1.
  if (n >= 1) {
    return k * pow_recursive(k, --n);
  } else {
    return 1;
  }
}

int main() {

  std::cout << "Raise a number k to power n using recursion.\n\n";
  float k = 0;
  float result = 0;
  int n = 0;

  while (true) {
    // Get user inputs for k and n.
    get_user_input(k, "number to raise to a power");

    do {
      get_user_input(n, "power to raise number to");
      if (n < 0) {
        // Ensure n < 0. Otherwise complain and retry.
        std::cout << std::format("{} has to be positive.\n", 'n');
        continue;
      }
    } while (n < 0);

    result = pow_recursive(k, n);
    std::cout << std::format("{0}^{1} is {2}\n\n", k, n, result);
  }

  return 0;
}

void get_user_input(auto &k, std::string k_char) {
  // Get input and validate it's an integer.
  bool is_valid = false;

  while (!is_valid) {
    std::cout << std::format("Enter {}: ", k_char);

    std::cin >> k;
    is_valid = std::cin.good();

    if (!is_valid) {
      std::cout << std::format("Error:\n* {} must be an integer.\n", k_char);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
