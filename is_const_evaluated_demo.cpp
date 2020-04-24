#include <iostream>
#include <type_traits>

constexpr int square(const int x) {
	if (std::is_constant_evaluated()) {
		return 1000 + x * x;
	}
	else {
		return x * x;
	}
}

int cube(const int x) {
	if (std::is_constant_evaluated()) {
		return 2000 + x * x * x;
	}
	else {
		return x * x * x;
	}
}


void is_const_evaluated_demo()
{

	int val_a = square(3);
	std::cout << val_a << std::endl;

	const int val_b = square(4);
	std::cout << val_b << std::endl;

	constexpr int val_c = square(5);
	std::cout << val_b << std::endl;

	const int val_d = square(val_a);
	std::cout << val_d << std::endl;

	int val_e = cube(7);
	std::cout << val_e << std::endl;

	const int val_f = cube(8);
	std::cout << val_f << std::endl;

}
