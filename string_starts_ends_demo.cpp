#include <iostream>
#include <string_view>
#include <string>

using namespace std::literals;

void string_demo()
{
	std::cout << "std::string:\n";

	const std::string cpp_demo{ "C++ 20 Demo" };
	std::string search_string{ "C++" };
	std::cout << "\"" << cpp_demo << "\" starts with \"" << search_string << "\": " << cpp_demo.starts_with(search_string) << "\n";

	search_string = "Java";
	std::cout << "\"" << cpp_demo << "\" starts with \"" << search_string << "\": " << cpp_demo.starts_with(search_string) << "\n";

	search_string = "Demo";
	std::cout << "\"" << cpp_demo << "\" ends with \"" << search_string << "\": " << cpp_demo.ends_with(search_string) << "\n";

	search_string = "demo";
	std::cout << "\"" << cpp_demo << "\" ends with \"" << search_string << "\": " << cpp_demo.ends_with(search_string) << "\n";

	std::cout << "\"" << cpp_demo << "\" starts with 'C': " << cpp_demo.starts_with('C') << "\n";
	std::cout << "\"" << cpp_demo << "\" starts with 'J': " << cpp_demo.starts_with('J') << "\n";

	const std::string cpp_demo_literal{ "My favorite programming language is\0\0C++"s };
	std::cout << "\"" << cpp_demo_literal << "\" ends with \"Java\"s: " << cpp_demo_literal.ends_with("Java"s) << "\n";
	std::cout << "\"" << cpp_demo_literal << "\" ends with \"C++\"s: " << cpp_demo_literal.ends_with("C++"s) << "\n";
}

void string_view_demo()
{
	std::cout << "std::string_view:\n";

	const std::string_view cpp_demo{ "This demo is for string_view" };

	std::string search_string{ "This" };
	std::cout << "\"" << cpp_demo << "\" starts with \"" << search_string << "\": " << cpp_demo.starts_with(search_string) << "\n";

	search_string = "That";
	std::cout << "\"" << cpp_demo << "\" starts with \"" << search_string << "\": " << cpp_demo.starts_with(search_string) << "\n";

	search_string = "view";
	std::cout << "\"" << cpp_demo << "\" ends with \"" << search_string << "\": " << cpp_demo.ends_with(search_string) << "\n";

	search_string = "something_else";
	std::cout << "\"" << cpp_demo << "\" ends with \"" << search_string << "\": " << cpp_demo.ends_with(search_string) << "\n";

	std::cout << "\"" << cpp_demo << "\" starts with 'T': " << cpp_demo.starts_with('T') << "\n";
	std::cout << "\"" << cpp_demo << "\" starts with 'X': " << cpp_demo.starts_with('X') << "\n";
}


void string_starts_ends_with_demo()
{
	// Set boolalpha format flag so bool values are represented by their textual representation: true or false
	std::boolalpha(std::cout);

	std::cout << "\nstring starts_with(), ends_with() demo:\n";

	string_demo();
	string_view_demo();
}