#include <iostream>

int summation_formula(int a, int b, int n);
int odd_sumation(int n);

int main() {

	// 1) Summation formula
	int a, b, n;
	std::cout << "Enter a: " << std::endl;
	std::cin >> a;
	std::cout << "Enter b: " << std::endl;
	std::cin >> b;
	std::cout << "Enter n: " << std::endl;
	std::cin >> n;

	int result = summation_formula(a, b, n);

	std::cout << "Result is " << result << std::endl;

	// 2) Sum of odd numbers
	int m = 0;
	std::cout << "Enter n: " << std::endl;
	std::cin >> m;

	int odd_numbers = odd_sumation(m);
	std::cout << "The sum of the first " << m << " odd numbers is " <<
		odd_numbers << std::endl;

	return 0;
} 

// 1) Solve summation formula
// sum_{i=a}^{b} i
// From inputs a, b, n, a <= b. Answer depends on a and b, not n
int summation_formula(int a, int b, int n) {
	int summation = 0;
	for (int n = a; n <= b; n++) {
		summation += n;
	}
	return summation;
}

// 2) Write a function that displays the sum of the first n odd numbers
int odd_sumation(int m) {
	int odds = 0;

	for (int i = 0; i < m; i++) {
		odds += 2*i + 1;
	}
	return odds;
}
