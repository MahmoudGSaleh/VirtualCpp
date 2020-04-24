#include <iostream>
#include <string_view>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std::literals;

struct transparent_string_hasher {
	using is_transparent = void; // For the lookup overloads to work, 'Hash::is_transparent' must be valid and denote a type
	size_t operator()(const std::string_view target) const noexcept {
		return std::hash<std::string_view>{}(target);
	}
};

// Alternatively, for this particular sample, std::equal_to<> could be used for 'Pred' template parameter, as in the unordered_set examples
struct transparent_string_equal {
	using is_transparent = void; // For the lookup overloads to work, 'Pred::is_transparent' must be valid and denote a type
	bool operator()(const std::string_view lhs, const std::string_view rhs) const noexcept {
		return lhs == rhs;
	}
};

void unordered_map_demo()
{
	std::cout << "std::unordered_map:\n";

	std::unordered_map<std::string, int, transparent_string_hasher, transparent_string_equal>  demo_unordered_map = {
		{"apples",  1},
		{"oranges", 2},
		{"bananas", 3} };

	std::string key = "apples";
	std::cout << "Key \"" << key << "\" found: " << demo_unordered_map.contains(key) << "\n";

	std::string_view k_view = "vegetables";
	std::cout << "Key \"" << k_view << "\"sv found: " << demo_unordered_map.contains(k_view) << "\n";

	std::cout << "Key \"bananas\"sv found: " << demo_unordered_map.contains("bananas"sv) << "\n";

	std::cout << "Key \"oranges\" found: " << (demo_unordered_map.find("oranges") != demo_unordered_map.end()) << "\n";

}

void unordered_set_demo()
{
	std::cout << "std::unordered_set:\n";

	std::unordered_set<std::string, transparent_string_hasher, std::equal_to<>>  demo_unordered_set = {
		{"apples"},
		{"oranges"},
		{"bananas"} };

	std::string key = "apples";
	std::cout << "Key \"" << key << "\" found: " << demo_unordered_set.contains(key) << "\n";

	std::string_view k_view = "vegetables";
	std::cout << "Key \"" << k_view << "\"sv found: " << demo_unordered_set.contains(k_view) << "\n";

	std::cout << "Key \"bananas\"sv found: " << demo_unordered_set.contains("bananas"sv) << "\n";

	std::cout << "Key \"oranges\" found: " << (demo_unordered_set.find("oranges") != demo_unordered_set.end()) << "\n";
}


void heterogeneous_unordered_lookup_demo()
{
	// Set boolalpha format flag so bool values are represented by their textual representation: true or false
	std::boolalpha(std::cout);

	std::cout << "\nheterogeneous unordered lookup demo:\n";

	unordered_map_demo();
	unordered_set_demo();
}
