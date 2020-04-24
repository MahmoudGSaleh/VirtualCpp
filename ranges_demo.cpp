// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

template<typename T, typename R>
constexpr void print_range(const char* message, const T& list, const R& result)
{
	std::cout << message << " { ";
	for (auto iter = list; iter != result.out; ++iter)
	{
		std::cout << "{" << *iter << "}, ";
	}
	std::cout << " }" << std::endl;
}

constexpr auto get_first = [](auto&& x) -> auto&& {
	return static_cast<decltype(x)>(x).first;
};
constexpr auto get_second = [](auto&& x) -> auto&& {
	return static_cast<decltype(x)>(x).second;
};

template<typename T>
void print_pairs(const char* message, const T& pairs)
{
	std::cout << message << " { ";
	for (auto const& pair : pairs)
	{
		std::cout << "{" << pair.first << ", " << pair.second << "}, ";
	}
	std::cout << " }" << std::endl;
}

void ranges_copy_demo()
{
	std::cout << "\nstd::ranges::copy()\n";

	int const input[] = { 1, 2, 3, 5, 8, 13, 21, 34, 45, 79 };
	int output[10] = { 0 };

	auto r1 = std::ranges::copy(input, output);
	print_range("copy output", output, r1);

	// copy number divisible by 3
	auto r2 = std::ranges::copy_if(input, output, [](const int i) {
		return i % 3 == 0;
		});
	print_range("copy_if %3 output", output, r2);

	// copy only non-negative numbers from a vector
	std::vector<int> v = { 25, 15, 5, 0, -5, -15 };
	auto r3 = std::ranges::copy_if(v, output, [](const int i) {
		return !(i < 0);
		});
	print_range("copy_if !(i < 0) output", output, r3);
}

void ranges_find_demo()
{
	std::cout << "\nstd::ranges::find()\n";

	std::array<std::pair<int, int>, 3> pairs = { {{17, 10}, {23, 13}, {0, 23}} };
	print_pairs("\nPairs", pairs);
	auto result = std::ranges::find(pairs, 23, get_second);
	if (result != std::end(pairs))
	{
		std::cout << "Found {*, 23} : " << "{ " << result->first << ", " << result->second << " }" << std::endl;
	}
	else
	{
		std::cout << "{*, 23} Not found!\n";
	}

	result = std::ranges::find(pairs, 73, get_first);
	if (result != std::end(pairs))
	{
		std::cout << "Found {73, *} : " << "{ " << result->first << ", " << result->second << " }" << std::endl;
	}
	else
	{
		std::cout << "{73, *} Not found!\n";
	}
}

void ranges_any_of_demo()
{
	std::cout << "\nstd::ranges::any_of()\n";

	auto is_even = [](auto const& x) { return x % 2 == 0; };
	auto is_odd = [](auto const& x) { return x % 2 != 0; };

	std::array<std::pair<int, int>, 3> pairs = { {{0, 13}, {7, 13}, {4, 13}} };
	print_pairs("\nPairs", pairs);

	auto result = std::ranges::any_of(pairs, is_even, get_first);
	std::cout << "Pairs range has even first: " << result << std::endl;

	result = std::ranges::any_of(pairs, is_even, get_second);
	std::cout << "Pairs range has even second: " << result << std::endl;

	result = std::ranges::any_of(pairs, is_odd, get_first);
	std::cout << "Pairs range has odd first: " << result << std::endl;

	result = std::ranges::any_of(pairs, is_odd, get_second);
	std::cout << "Pairs range has odd second: " << result << std::endl;

}

void ranges_demo()
{
	// Set boolalpha format flag so bool values are represented by their textual representation: true or false
	std::boolalpha(std::cout);
	std::cout << "\nstd::ranges demo:\n";

	ranges_copy_demo();
	ranges_find_demo();
	ranges_any_of_demo();

	// Not all algoritms are demo'ed. Implemented algorithms are:
	//   copy / copy_n / copy_if
	//   all_of / any_of / none_of
	//   find / find_if / find_if_not
	//   count / count_if
	//   for_each / for_each_n
	//   equal / mismatch

}
