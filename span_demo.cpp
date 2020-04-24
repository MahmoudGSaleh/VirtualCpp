// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <iostream>
#include <algorithm>
#include <array>
#include <span>
#include <string>
#include <vector>

template<typename T>
void print_span(std::span<T> span)
{
	std::cout << "[";
	for (const auto& element : span)
	{
		std::cout << element << ", ";
	}
	std::cout << "] (" << span.size() << " elements)\n";
}

void modify_span_elements()
{
	std::cout << "\nmodify span demo:\n";

	std::vector<std::string> vector_of_str = { "span", "view", "contigeous" };
	std::span<std::string> span_of_str(vector_of_str);

	print_span<std::string>(span_of_str);

	// Modify individual elements
	for (auto&& str : span_of_str) {
		str[0] = (char)std::toupper(str[0]);
	}

	print_span<std::string>(span_of_str);
}

void create_span()
{
	std::cout << "\ncreate span demo:\n";

	std::array int_array = std::to_array({ 1, 2, 4 });
	print_span<int>(int_array);

	std::vector<int> int_vector = { 1, 2, 3, 5, 7, 10 };
	print_span<int>(int_vector);

	std::span<int> int_span(int_vector);
	print_span<int>(int_span);

	std::span<int> another_int_span(int_vector.begin(), int_vector.end());
	print_span<int>(int_span);

	// This won't work since span is non-owning and the argument cannot be referenced
	// std::span<int> another_int_span(std::to_array({ 1, 2, 4 }));
}

void iterate_span()
{
	std::cout << "\niterate span demo:\n";

	std::vector<std::string> vector_of_str = { "span", "view", "contiguous" };
	std::span<std::string> span_of_str(vector_of_str);

	for (auto&& str : span_of_str)
	{
		std::cout << "\"" << str << "\" ";
	}
	std::cout << std::endl;

	// Using commonly used iterators
	for (auto it = span_of_str.rbegin(); it < span_of_str.rend(); ++it)
	{
		std::cout << "\"" << *it << "\" ";
	}
	std::cout << std::endl;

	// Or even good old fashioned for loops
	for (size_t i = 0; i < span_of_str.size(); i++)
	{
		std::cout << "\"" << span_of_str[i] << "\" ";
	}
	std::cout << std::endl;
}

void span_demo()
{
	create_span();

	modify_span_elements();

	iterate_span();
}
