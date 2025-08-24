#include <format>
#include <iostream>
#include <string>

int summation();
int odd_summation();
void get_user_input(auto &k, std::string k_char);

int main() {
  // An option to let user select which function to call.
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
  // We pass a variable by reference and a description of it.
  // Then the function prompts the user to enter a value for the variable.
  bool is_valid = false;

  while (!is_valid) {
    std::cout << std::format("Enter {}: ", k_char);

    std::cin >> k;
    is_valid = std::cin.good();

    if (!is_valid) {
      // Validates the input by using std::cin.good() which returns
      // true or false according to whether input is 'good' or not.
      // Complains if input is bad and asks user to try again.
      std::cout << std::format("Error:\n* {} must be an integer.\n", k_char);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

// 1) Solve summation formula
int summation() {
  // sum_{i=a}^{b} i
  // From inputs a, b, n, a <= b. Answer depends on a and b, not n
  int a, b, n;
  bool is_validinput = false;

  int result = 0;

  while (!is_validinput) {
    // Get input from the user until it's valid.

    get_user_input(a, "a");
    get_user_input(b, "b");
    is_validinput = a <= b;
    if (!is_validinput) {
      // Validate user input to ensure a >= b.
      // Complain and retry if a < b.
      std::cout << "Error: a has to be less than or equal to b.\n\n";
      continue;
    }
    get_user_input(n, "n");
  }

  // Set n = a and sum each successive n (adding 1 each step).
  for (int n = a; n <= b; n++) {
    result += n;
  }

  return result;
}

// 2) Write a function that displays the sum of the first n odd numbers.
int odd_summation() {
  int n;
  int result = 0;
  bool is_n_positive = false;

  while (!is_n_positive) {
    // Get input from user until it's valid.
    get_user_input(n, "n");

    is_n_positive = n > 0;

    if (!is_n_positive) {
      // Ensure n is positive. Otherwise complain and retry.
      std::cout << "n has to be a positive integer.\n";
    }
  }

  // Then add each number of the form 2k + 1 where k ranges from 0 to n.
  // This is, of course, nothing more and nothing less than the sum of the first
  // n odd numbers.
  for (int k = 0; k < n; k++) {
    result += (2 * k) + 1;
  }

  return result;
}
