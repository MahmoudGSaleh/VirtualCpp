// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Demos MSVC STL implementation for https://wg21.link/P1209R0 

#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

// To demonstrate deprecation
// #include <experimental/string>

struct is_vowel
{
	bool operator()(const char c) const
	{
		return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
	}
};

struct is_odd
{
	bool operator()(const int i) const
	{
		return i % 2 != 0;
	}
};

struct is_first_odd
{
	bool operator()(const std::pair<const int, int>& p) const
	{
		return p.first % 2 != 0;
	}
};

template<typename T>
void print_list(const char* message, const T& list)
{
	std::cout << message << ": { ";
	for (auto const& element : list)
	{
		std::cout << element << " ";
	}
	std::cout << " }; size = " << list.size() << std::endl;
}

template<typename T>
void print_map(const char* message, const T& map)
{
	std::cout << message << ": { ";
	for (auto const& pair : map)
	{
		std::cout << "{" << pair.first << ", " << pair.second << "} ";
	}
	std::cout << " }; size = " << map.size() << std::endl;
}

void erase_demo()
{
	// NOTE: the examples here are compiled against VS 16.6, which didn't include an implementation for P1115R3: https://wg21.link/P1115R3
	// P1115R3 requires erase() and erase_if() to return the number of removed elements
	// GH-566 (https://github.com/microsoft/STL/pull/566) fixes that and the fix will be included in VS 16.7.
	// TODO: Update the samples to account for return of erase() and erase_if()

	std::cout << "\nerase() demo\n";

	// NOTE: std::experimental::erase() has been deprecated. If used in C++20, a warning like this will be issued:
	//    Error	C4996	'std::experimental::fundamentals_v2::erase': warning STL4026 : std::experimental::erase() and std::experimental::erase_if()
	//    are deprecated by Microsoft and will be REMOVED. They are superseded by std::erase() and std::erase_if().
	//    You can define _SILENCE_EXPERIMENTAL_ERASE_DEPRECATION_WARNING to acknowledge that you have received this warning.

	//std::experimental::erase(str2, 'u');

	std::string str{ "visual studio" };
	std::cout << "Before erase: \"" << str << "\"; size = " << str.size() << std::endl;
	std::erase(str, 'u');
	std::cout << "After erase: \"" << str << "\"; size = " << str.size() << std::endl;

	std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };
	print_list("Before erase", v);
	std::erase(v, 4);
	print_list("After erase", v);

	std::list<int> l{ 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };
	print_list("Before erase", l);
	std::erase(l, 4);
	print_list("After erase", l);
}

void erase_if_demo()
{
	std::cout << "\nerase_if() demo\n";

	std::string str{ "cute fluffy kittens" };
	std::cout << "Before erase_if: \"" << str << "\"; size = " << str.size() << std::endl;
	std::erase_if(str, is_vowel{});
	std::cout << "After erase_if: \"" << str << "\"; size = " << str.size() << std::endl;

	std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };
	print_list("Before erase_if", v);
	std::erase_if(v, is_odd{});
	print_list("After erase_if", v);

	std::set<int> s{ 1, 2, 3, 4, 5, 6, 7 };
	print_list("Before erase_if", s);
	std::erase_if(s, is_odd{});
	print_list("After erase_if", s);

	std::map<int, int> m{ {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}, {6, 60}, {7, 70} };
	print_map("Before erase_if", m);
	std::erase_if(m, is_first_odd{});
	print_map("After erase_if", m);

	std::unordered_map<int, int> um{ {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}, {6, 60}, {7, 70} };
	print_map("Before erase_if", um);
	std::erase_if(um, is_first_odd{});
	print_map("After erase_if", um);
}

void consistent_container_erasure_demo()
{
	std::cout << "\nerase() and erase_if() demo:\n";

	erase_demo();
	erase_if_demo();
}
