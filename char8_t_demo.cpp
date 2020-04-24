#include <limits>
#include <filesystem>
#include <iostream>
#include <string>

// For MultiByteToWideChar()
#include <windows.h>

// Helper functions
bool u8string_to_wstring(const std::u8string& input_str, std::wstring& output_str)
{
	const auto raw_input_size = input_str.size();
	if (raw_input_size > (std::numeric_limits<int>::max)()) {
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

void char8_t_basic_demo()
{
	// The following now fails in C++20 (ill-formed). It was well-formed in C++17 and C++14
	//   error C2440 : 'initializing' : cannot convert from 'const char8_t [31]' to 'const char *'
	//   message : Types pointed to are unrelated; conversion requires reinterpret_cast, C-style cast or function-style cast

	// const char* old_str = u8"This is a UTF-8 encoded string";

	const char8_t* char8_str = u8"This is UTF-8 string";

	std::u8string my_str = char8_str;
	// Can also be declared like this
	// std::u8string my_str = u8"This is UTF-8 string";


	// There is no easy way to print utf8 strings directly, so we convert to wstring first, and use wcout
	std::wstring my_wstr{};
	u8string_to_wstring(my_str, my_wstr);

	// traits starts_with
	bool starts_with = my_str.starts_with(u8"This");
	std::wcout << "\"" << my_wstr << "\" starts with \"This\": " << starts_with << "\n";

	// hash
	std::size_t str_hash = std::hash<std::u8string>{}(my_str);
	std::size_t str_whash = std::hash<std::wstring>{}(my_wstr);

	std::wcout << L"hash(u8" << std::quoted(my_wstr) << ") = " << str_hash << '\n';
	std::wcout << L"hash(L" << std::quoted(my_wstr) << ") = " << str_whash << '\n';
}

void char8_t_path_demo()
{
	// 'u8path' is deprecated in C++20
	//    error C4996 : 'std::filesystem::u8path' :
	//    warning STL4021 : The std::filesystem::u8path() overloads are deprecated in C++20.
	//    The constructors of std::filesystem::path provide equivalent functionality via construction from u8string, u8string_view,
	//    or iterators with value_type char8_t. You can define _SILENCE_CXX20_U8PATH_DEPRECATION_WARNING or _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS
	//    to acknowledge that you have received this warning.

	// auto path = std::filesystem::u8path("filename");

	// Instead we use a new specialized path for <char8_t>
	std::u8string my_file_path = u8"C:\\RootFolder\\MyFile.txt";
	std::filesystem::path my_path = std::filesystem::path(my_file_path);
	std::cout << "File path: " << my_path << '\n'
		<< "file name: " << my_path.filename() << '\n'
		<< "relative path: " << my_path.relative_path() << '\n'
		<< "extension: " << my_path.extension() << '\n';
}

void char8_t_demo()
{
	// Set boolalpha format flag so bool values are represented by their textual representation: true or false
	std::boolalpha(std::wcout);
	std::boolalpha(std::cout);

	std::cout << "\nchar8_t demo:\n";

	char8_t_basic_demo();
	char8_t_path_demo();
}
