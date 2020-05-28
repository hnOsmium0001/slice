#include <cstddef>
#include <iterator>

namespace hn {

template <typename Iterator>
class Slice {
public:
	using Traits = std::iterator_traits<Iterator>;
	using Distance = typename Traits::difference_type;
	using ValueType = typename Traits::value_type;
	using RefValueType = typename Traits::reference;

private:
	Iterator beg_;
	size_t size_;

public:
	static auto None(Iterator end) -> Slice {
		return Slice{end, 0};
	}
	static auto Between(Iterator begin, Iterator end) -> Slice {
		return Slice{begin, begin + std::distance(begin, end)};
	}
	static auto At(Iterator begin, Distance size) -> Slice {
		return Slice{begin, size};
	}

	Slice(Iterator begin, size_t size) noexcept
		: beg_{ begin }
		, size_{ size } {}
	
	auto begin() const -> Iterator { return beg_; }
	auto end() const -> Iterator { return beg_ + size_; }
	auto size() const -> size_t { return size_; }
};

template <typename Container>
using RegularSlice = Slice<typename Container::iterator>;
template <typename Container>
using ConstSlice = Slice<typename Container::const_iterator>;

} // namespace hn
