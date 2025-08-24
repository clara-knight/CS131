#include <format>
#include <iostream>
#include <string>

int summation();
int odd_summation();
void get_user_input(auto &k, std::string k_char);

int main() {

  char opt;

  std::cout << "1) Summation formula.\n\n2) First n odd numbers.\n";

  while (true) {
    get_user_input(opt, "Option");

    switch (opt) {
    case '1':
      std::cout << std::format("The resuls is {}.\n\n", summation());
      break;

    case '2':
      std::cout << std::format("The resuls is {}.\n\n", odd_summation());
      break;

    default:
      std::cout << "Incorrect option.\n";
      break;
    }
  }

  return 0;
}

void get_user_input(auto &k, std::string k_char) {
  bool is_int = false;

  while (!is_int) {
    std::cout << std::format("Enter {}: ", k_char);

    std::cin >> k;
    is_int = std::cin.good();

    if (!is_int) {
      std::cout << std::format("Error: {} must be an integer.\n", k_char);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

// 1) Solve summation formula
// sum_{i=a}^{b} i
// From inputs a, b, n, a <= b. Answer depends on a and b, not n
int summation() {
  int a, b, n;
  bool is_validinput = false;

  int result = 0;

  while (!is_validinput) {

    get_user_input(a, "a");
    get_user_input(b, "b");
    is_validinput = a <= b;
    if (!is_validinput) {
      std::cout << "Error: a has to be less than or equal to b.\n\n";
      continue;
    }
    get_user_input(n, "n");
  }

  for (int n = a; n <= b; n++) {
    result += n;
  }

  return result;
}

// 2) Write a function that displays the sum of the first n odd numbers
int odd_summation() {
  int n;
  int result = 0;
  bool is_n_positive = false;

  while (!is_n_positive) {
    get_user_input(n, "n");

    is_n_positive = n > 0;

    if (!is_n_positive) {
      std::cout << "n has to be a positive integer.\n";
    }
  }

  for (int j = 0; j < n; j++) {
    result += (2 * j) + 1;
  }

  return result;
}
