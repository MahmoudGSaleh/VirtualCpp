// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <iostream>
#include <charconv>
#include <system_error>
#include <string_view>
#include <array>
#include <algorithm>

void to_chars_demo()
{
	std::cout << "\nto_chars:\n";
	std::array<char, 20> chars_array;

	std::to_chars_result result = std::to_chars(chars_array.data(), chars_array.data() + chars_array.size(), 727);
	std::cout << std::string_view(chars_array.data(), std::distance(chars_array.data(), result.ptr))
		<< "; ec: " << static_cast<int>(result.ec) << std::endl;

	result = std::to_chars(chars_array.data(), chars_array.data() + chars_array.size(), 727, 16 /* hex */);
	std::cout << std::string_view(chars_array.data(), std::distance(chars_array.data(), result.ptr))
		<< "; ec: " << static_cast<int>(result.ec) << std::endl;

	result = std::to_chars(chars_array.data(), chars_array.data() + chars_array.size(), 727, 2 /* binary */);
	std::cout << std::string_view(chars_array.data(), std::distance(chars_array.data(), result.ptr))
		<< "; ec: " << static_cast<int>(result.ec) << std::endl;

	result = std::to_chars(chars_array.data(), chars_array.data() + chars_array.size(), 22 / 7.0);
	std::cout << std::string_view(chars_array.data(), std::distance(chars_array.data(), result.ptr))
		<< "; ec: " << static_cast<int>(result.ec) << std::endl;

	result = std::to_chars(chars_array.data(), chars_array.data() + chars_array.size(), static_cast<long double>(72230340329497), std::chars_format::scientific, 6);
	std::cout << std::string_view(chars_array.data(), std::distance(chars_array.data(), result.ptr))
		<< "; ec: " << static_cast<int>(result.ec) << std::endl;
}

void from_chars_demo()
{
	std::cout << "\nfrom_chars:\n";

	double value;

	// For simplicity, we'll reuse one char array of 4 elements for input
	std::array chars_array = std::to_array("2020");
	std::from_chars_result result = std::from_chars(chars_array.data(), chars_array.data() + chars_array.size(), value);
	std::cout << value << "; ec: " << static_cast<int>(result.ec) << std::endl;

	chars_array = std::to_array("3.14");
	result = std::from_chars(chars_array.data(), chars_array.data() + chars_array.size(), value);
	std::cout << value << "; ec: " << static_cast<int>(result.ec) << std::endl;

	chars_array = std::to_array("12e4"); // scientific 12x10^4
	result = std::from_chars(chars_array.data(), chars_array.data() + chars_array.size(), value, std::chars_format::scientific);
	std::cout << value << "; ec: " << static_cast<int>(result.ec) << std::endl;

	chars_array = std::to_array("abcd"); // hex for 43981
	result = std::from_chars(chars_array.data(), chars_array.data() + chars_array.size(), value, std::chars_format::hex);
	std::cout << value << "; ec: " << static_cast<int>(result.ec) << std::endl;

	chars_array = std::to_array("0101"); // binary for 5
	short binary_value;
	result = std::from_chars(chars_array.data(), chars_array.data() + chars_array.size(), binary_value, 2);
	std::cout << binary_value << "; ec: " << static_cast<int>(result.ec) << std::endl;

	chars_array = std::to_array("nval"); // invalid input
	result = std::from_chars(chars_array.data(), chars_array.data() + chars_array.size(), value);
	std::cout << value << "; ec: " << static_cast<int>(result.ec) << std::endl;
}

void charconv_demo()
{
	std::cout << "\nElementary string conversion demo:\n";

	to_chars_demo();
	from_chars_demo();
}
