#include <iostream>
#include <vector>
#include <hn/Slice.hpp>

using hn::ConstSlice;

int main() {
	std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8};
	auto slice = ConstSlice<std::vector<int>>::At(vec.begin(), 4); // [1, 2, 3, 4]
	for (auto& val : slice) std::cout << val << ", ";
	return 0;
}
