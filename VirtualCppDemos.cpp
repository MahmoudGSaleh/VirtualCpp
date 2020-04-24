// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// C++ features demos
void associative_container_contains_demo();
void string_starts_ends_with_demo();
void char8_t_demo();
void charconv_demo();
void heterogeneous_unordered_lookup_demo();
void consistent_container_erasure_demo();
void is_constant_evaluated_demo();
void constexpr_for_algorithm_and_utility_demo();
void span_demo();
void ranges_demo();

int main()
{
	// 1: Associative container contains() Demo
	//associative_container_contains_demo();

	// 2: String Prefix and Suffix Checking
	//string_starts_ends_with_demo();

	// 3: char8_t: A type for UTF-8 characters and strings
	//char8_t_demo();

	// 4. Elementary character conversion
	//charconv_demo();

	// 5: Heterogeneous lookup for unordered containers
	//heterogeneous_unordered_lookup_demo();

	// 6. Consistent Container Erasure from Library Fundamentals 2
	//consistent_container_erasure_demo();

	// 7. std::is_constant_evaluated()
	//is_constant_evaluated_demo();

	// 8. constexpr for <algorithm> And <utility>
	constexpr_for_algorithm_and_utility_demo();

	// 9. <span>
	//span_demo();

	// 10. <ranges>
	//ranges_demo();


}
