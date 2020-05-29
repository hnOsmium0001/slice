#include <cstddef>
#include <utility>
#include <functional>
#include <iterator>

namespace hn {

template <class Iterator>
class Slice {
public:
	using Traits = std::iterator_traits<Iterator>;
	using Distance = typename Traits::difference_type;
	using ValueType = typename Traits::value_type;
	using RefValueType = typename Traits::reference;

private:
	Iterator beg_;
	Distance size_;

public:
	static auto None(Iterator end) -> Slice {
		return Slice{end, 0};
	}
	static auto Between(Iterator begin, Iterator end) -> Slice {
		return Slice{begin, std::distance(begin, end)};
	}
	static auto At(Iterator begin, Distance size) -> Slice {
		return Slice{begin, size};
	}

	Slice(Iterator begin, Distance size) noexcept
		: beg_{ std::move(begin) }
		, size_{ std::move(size) } {}
	
	Slice(const Slice&) noexcept = default;
	Slice& operator=(const Slice&) noexcept = default;
	Slice(Slice&&) noexcept = default;
	Slice& operator=(Slice&&) noexcept = default;
	
	auto begin() const -> Iterator { return beg_; }
	auto end() const -> Iterator { return std::next(beg_, size_); }
	auto size() const -> Distance { return size_; }

	auto operator[](Distance idx) -> RefValueType { return beg_[idx]; }

	/// Decrease the size of this slice by `shrinkage`.
	/// 
	/// Notice this method may cause undefined behavior if the parameter `shrinkage` is larger
	/// than the size of this slice.
	auto Shrink(Distance shrinkage) -> Slice {
		return Slice{beg_, size_ - shrinkage};
	}

	/// Increase the size of this slice by `growth`.
	/// 
	/// Notice this method may cause undefined behavior if the parameter `growth` causes the end
	/// of this slice to be after the end of the underlying container.
	auto Grow(Distance growth) -> Slice {
		return Slice{beg_, size_ + growth};
	}

	auto Narrow(Distance left, Distance right) -> Slice {
		return Slice{std::next(beg_, left), size_ - left - right};
	}

	auto Expand(Distance left, Distance right) -> Slice {
		return Slice{std::prev(beg_, left), size_ + left + right};
	}
};

template <class Container>
using RegularSlice = Slice<typename Container::iterator>;
template <class Container>
using ConstSlice = Slice<typename Container::const_iterator>;

/// Creates a slice with range `[beginIdx, endIdx)`. Syntax sugar that's designed to simplify
/// creating slces from containers.
/// 
/// Example:
/// ```cpp
/// auto vec = std::vector<int>{0, 1, 2, 3, 4, 5};
/// auto part_plainSyntax = RegularSlice<std::vector<int>>{vec.begin() + 1, 3}; // Yields [1, 2, 3]
/// auto part_sugaredSyntax = sliceOf(vec, 1, 4); // Yields [1, 2, 3]
/// ```
template <class Container>
auto SliceOf(
	Container& container,
	typename RegularSlice<Container>::Distance beginIdx,
	typename RegularSlice<Container>::Distance endIdx
) -> RegularSlice<Container> {
	return RegularSlice<Container>::At(container.begin() + beginIdx, endIdx - beginIdx);
}

template <class Container>
auto SliceOf(
	const Container& container,
	typename ConstSlice<Container>::Distance beginIdx,
	typename ConstSlice<Container>::Distance endIdx
) -> ConstSlice<Container> {
	return ConstSlice<Container>::At(container.begin() + beginIdx, endIdx - beginIdx);
}

} // namespace hn
