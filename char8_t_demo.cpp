// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Demos MSVC STL implementation for https://wg21.link/P0482R6

#include <limits>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <string>

// For MultiByteToWideChar()
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

// Helper functions
bool u8string_to_wstring(const std::u8string& input_str, std::wstring& output_str)
{
	const auto raw_input_size = input_str.size();
	if (raw_input_size > static_cast<size_t>((std::numeric_limits<int>::max)()))
	{
		return false;
	}

	int clamped_input_size = static_cast<int>(raw_input_size);
	int count_output_chars = ::MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(input_str.data()), clamped_input_size, nullptr, 0);

	if (count_output_chars == 0)
	{
		return false;
	}

	output_str.resize(count_output_chars);
	return (::MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(input_str.data()), clamped_input_size, output_str.data(), count_output_chars) > 0);
}

void char8_t_usage_demo()
{
	std::wcout << L"\nchar8_t usage demo:\n";

	// The following now fails in C++20 (ill-formed). It was well-formed in C++17 and C++14
	//   error C2440 : 'initializing' : cannot convert from 'const char8_t [31]' to 'const char *'
	//   message : Types pointed to are unrelated; conversion requires reinterpret_cast, C-style cast or function-style cast

	// const char* old_str = u8"Ťhįş įş ä ÚŤF-8 ştrįng";

	const char8_t* char8_str = u8"Ťhįş įş ä ÚŤF-8 ştrįng";

	std::u8string u8_str = char8_str;
	// Can also be declared like this
	// std::u8string u8_str = u8"Ťhįş įş ä ÚŤF-8 ştrįng";

	std::u8string u8_search_str = u8"Ťhįş";

	// traits starts_with
	bool starts_with = u8_str.starts_with(u8_search_str);

	// There is no straightforward way to print utf8 strings directly to the console, so we convert to wstring first, and use std::wcout
	std::wstring w_str{};
	u8string_to_wstring(u8_str, w_str);

	std::wstring w_search_str{};
	u8string_to_wstring(u8_search_str, w_search_str);

	std::wcout << std::quoted(w_str) << L".starts_with(" << std::quoted(w_search_str) << "): " << starts_with << std::endl;

	// hash
	std::size_t u8_str_hash = std::hash<std::u8string>{}(u8_str);
	std::size_t w_str_whash = std::hash<std::wstring>{}(w_str);

	std::wcout << L"hash(u8" << std::quoted(w_str) << ") = 0x" << std::hex << u8_str_hash << std::endl;
	std::wcout << L"hash(L" << std::quoted(w_str) << ") = 0x" << std::hex << w_str_whash << std::endl;
}

void char8_t_path_demo()
{
	std::wcout << L"\nchar8_t path demo:\n";

	// 'u8path' is deprecated in C++20
	//    error C4996 : 'std::filesystem::u8path' :
	//    warning STL4021 : The std::filesystem::u8path() overloads are deprecated in C++20.
	//    The constructors of std::filesystem::path provide equivalent functionality via construction from u8string, u8string_view,
	//    or iterators with value_type char8_t. You can define _SILENCE_CXX20_U8PATH_DEPRECATION_WARNING or _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS
	//    to acknowledge that you have received this warning.

	// auto path = std::filesystem::u8path("filename");

	// Instead we use a new specialized path for <char8_t>
	std::u8string my_file_path = u8R"("C:\Windows\System32\ŚŎMĘ FĨĻĔ.ēxţ")";
	std::filesystem::path my_path(my_file_path);
	std::wcout << L"File path: " << my_path << std::endl
		<< L"file name: " << my_path.filename() << std::endl
		<< L"relative path: " << my_path.relative_path() << std::endl
		<< L"extension: " << my_path.extension() << std::endl;
}

void char8_t_demo()
{
	// Windows specific: Enable output of wide char strings with non-ASCII to stdout
	// Note, after setting this, narrow char printing to stdout will not work
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Set boolalpha format flag so bool values are represented by their textual representation: true or false
	std::boolalpha(std::wcout);


	std::wcout << L"\nchar8_t demo:\n";

	char8_t_usage_demo();
	char8_t_path_demo();
}
