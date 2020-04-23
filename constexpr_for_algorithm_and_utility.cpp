
#include <array>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>

// Examples of constexpr code that can now be compiled in C++20
constexpr void constexpr_for_each()
{
	constexpr std::array a = std::to_array("Hello C++20");
	std::for_each(a.begin(), a.end(), [](char c) { /* Do something with c */ });
}

constexpr void constexpr_replace()
{
	std::array<int, 10> a{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::replace(a.begin(), a.end(), 1, 0);
}

constexpr void constexpr_remove()
{
	std::array<int, 10> a{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto r = std::remove(a.begin(), a.end(), 1);
}

constexpr void constexpr_exchange()
{
	int x = 1;
	int y = 2;
	auto r = std::exchange(x, y);
}

void constexpr_for_algorithm_and_utility_demo()
{
	// Using an example from the feature proposal: http://wg21.link/P0202R3   

	// OK
	constexpr std::array<char, 6> a{ 'H', 'e', 'l', 'l', 'o' };

	// Compilation of the following will fail in C++17, with the following error:
	//   error C2131 : expression did not evaluate to a constant
	//   message : failure was caused by call of undefined function or one not declared 'constexpr'
	//   message : see usage of 'std::find'


	// std::find is now constexpr
	// Compiles with no errors in C++20 /std:c++latest
	constexpr auto it = std::find(a.rbegin(), a.rend(), 'H');

	// Other examples of algoritms that are now constexpr in C++20
	
	constexpr std::array<char, 6> a2{ 'H', 'e', 'l', 'l', 'o' };
	constexpr auto b = std::equal(a.begin(), a.end(), a2.begin());
	constexpr auto r = std::equal_range(a.begin(), a.end(), 'H');
	constexpr auto s = std::binary_search(a.begin(), a.end(), 'H');
}