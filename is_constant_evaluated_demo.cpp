// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Demos MSVC STL implementation for https://wg21.link/P0595R2

#include <iostream>
#include <type_traits>

constexpr int square(const int x)
{
	if (std::is_constant_evaluated())
	{
		return 1000 + x * x;
	}
	else
	{
		return x * x;
	}
}

/*constexpr*/ int cube(const int x)
{
	if (std::is_constant_evaluated())
	{
		return 2000 + x * x * x;
	}
	else
	{
		return x * x * x;
	}
}

void is_constant_evaluated_demo()
{
	int val_a = square(2);
	std::cout << "square(2) = " << val_a << std::endl;

	const int val_b = square(3);
	std::cout << "square(3) = " << val_b << std::endl;

	constexpr int val_c = square(5);
	std::cout << "square(5) = " << val_b << std::endl;

	const int val_d = square(val_a);
	std::cout << "square(val_a) = " << val_d << std::endl;

	int val_e = cube(7);
	std::cout << "cube(7) = " << val_e << std::endl;

	const int val_f = cube(8);
	std::cout << "cube(8) = " << val_f << std::endl;

	// This will not compile because because cube() is not constexpr:
	// C2131: expression did not evaluate to a constant
	// constexpr int val_g = cube(9);
}
