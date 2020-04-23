#include <iostream>
#include <algorithm>
#include <array>
#include <span>
#include <vector>

/* --------------------------------------------- */
/* --------------------------------------------- */
/* --------------------------------------------- */
/* span is still WIP, but demo ideas are welcome */
/* --------------------------------------------- */
/* --------------------------------------------- */
/* --------------------------------------------- */

template<typename T>
void print_content(std::span<T> container)
{
	for (const auto& e : container)
	{
		std::cout << e;
	}
	std::cout << '\n';
}

void span_demo()
{
	std::array s = std::to_array({ 1, 2, 4 });
	print_content<int>(s);

	std::vector<int> v = { 1, 2, 3, 5, 7, 10 };
	print_content<int>(s);
}
