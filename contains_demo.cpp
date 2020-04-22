#include <iostream>
#include <set>
#include <unordered_map>

void set_contains_demo()
{
	std::cout << "std::set:\n";

	std::set<int> demo_set = { 15, 10, 35, 25 };

	int key = 10;
	std::cout << "Key \"" << key << "\" found: " << demo_set.contains(key) << "\n";

	// The old way is a bit more obscure
	// std::cout << "Key \"" << key << "\" found: " << (demo_set.find(key) != demo_set.end()) << "\n";

	key = 30;
	std::cout << "Key \"" << key << "\" found: " << demo_set.contains(key) << "\n";
}

void unordered_map_contains_demo()
{
	std::cout << "std::unordered_map:\n";
	std::unordered_map<int, char> demo_unordered_map = { {10, 'a'}, {20, 'b'} };

	int key = 10;
	std::cout << "Key \"" << key << "\" found: " << demo_unordered_map.contains(key) << "\n";

	key = 30;
	std::cout << "Key \"" << key << "\" found: " << demo_unordered_map.contains(key) << "\n";
}

void associative_container_contains_demo()
{
	// Set boolalpha format flag so bool values are represented by their textual representation: true or false
	std::boolalpha(std::cout);
	std::cout << "\nassociative container contains() demo:\n";

	set_contains_demo();
	unordered_map_contains_demo();
}
