#include <iostream>
#include <vector>
#include <hn/Slice.hpp>

int main() {
	std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8};
	{
		auto slice = hn::ConstSlice<std::vector<int>>::At(vec.begin(), 4);
		for (auto& val : slice) std::cout << val << ", "; // [1, 2, 3, 4]
		std::cout << "\n";
	}
	{
		auto slice = hn::SliceOf(vec, 5, 8);
		for (auto& val : slice) std::cout <<val << ", "; // [6, 7, 8]
		std::cout << "\n";
	}
	return 0;
}
