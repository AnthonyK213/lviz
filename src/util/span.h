#ifndef _LVIZ_UTIL_SPAN_T
#define _LVIZ_UTIL_SPAN_T

#include <array>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

namespace lviz {
namespace util {

struct contract_violation_error : std::logic_error {
  explicit contract_violation_error(const char *msg) : std::logic_error(msg) {}
};

inline void contract_violation(const char *msg) {
  throw contract_violation_error(msg);
}

#define LVIZ_UTIL_SPAN_EXPECT(cond, msg)                                       \
  (cond) ? (void)0 : contract_violation(msg)

inline constexpr std::size_t dynamic_extent = static_cast<std::size_t>(-1);

template <class T, std::size_t Extent> class span;

namespace detail {

template <class T, std::size_t Extent> struct span_extent_type {
  using pointer = T *;

  constexpr span_extent_type() noexcept = default;

  constexpr explicit span_extent_type(const pointer data, std::size_t) noexcept
      : data_(data) {}

  pointer data_ = nullptr;
  static constexpr std::size_t size_ = Extent;
};

template <class T> struct span_extent_type<T, dynamic_extent> {
  using pointer = T *;

  constexpr span_extent_type() noexcept = default;

  constexpr explicit span_extent_type(const pointer data,
                                      std::size_t size) noexcept
      : data_(data), size_(size) {}

  pointer data_ = nullptr;
  std::size_t size_ = 0;
};

template <class> constexpr bool is_span_v = false;

template <class T, std::size_t Extent>
constexpr bool is_span_v<span<T, Extent>> = true;

template <class> constexpr bool is_std_array_v = false;

template <class T, std::size_t N>
constexpr bool is_std_array_v<std::array<T, N>> = true;

template <class T> struct remove_cvref {
  using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

} // namespace detail

template <class T, std::size_t Extent = dynamic_extent>
class span : private detail::span_extent_type<T, Extent> {
private:
  using base_ = detail::span_extent_type<T, Extent>;
  using base_::data_;
  using base_::size_;

public:
  using element_type = T;
  using value_type = std::remove_cv_t<T>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using iterator = pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;

  static constexpr size_type extent = Extent;

public:
  constexpr span() noexcept : base_() {
    static_assert(Extent == 0 || Extent == dynamic_extent,
                  "Cannot construct empty span with non-zero static extent");
  }

  constexpr span(pointer first, size_type count) : base_(first, count) {
    if constexpr (extent != dynamic_extent) {
      LVIZ_UTIL_SPAN_EXPECT(count == extent,
                            "Cannot construct span with static extent");
    }
  }

  constexpr span(pointer first, pointer last)
      : base_(first, static_cast<size_type>(last - first)) {
    if constexpr (extent != dynamic_extent) {
      LVIZ_UTIL_SPAN_EXPECT(last - first == extent,
                            "Cannot construct span with static extent");
    }
  }

  template <size_type N, typename std::enable_if_t<
                             Extent == dynamic_extent || Extent == N, int> = 0>
  constexpr span(element_type (&arr)[N]) noexcept : base_(arr, N) {}

  template <class U, size_type N,
            typename std::enable_if_t<
                (Extent == dynamic_extent || Extent == N) &&
                    std::is_convertible_v<U (*)[], element_type (*)[]>,
                int> = 0>
  constexpr span(std::array<U, N> &arr) noexcept
      : base_(arr.data(), arr.size()) {}

  template <class U, size_type N,
            typename std::enable_if_t<
                (Extent == dynamic_extent || Extent == N) &&
                    std::is_convertible_v<const U (*)[], element_type (*)[]>,
                int> = 0>
  constexpr span(const std::array<U, N> &arr) noexcept
      : base_(arr.data(), arr.size()) {}

  template <
      class R,
      typename std::enable_if_t<
          !std::is_array_v<typename detail::remove_cvref<R>::type> &&
              !detail::is_span_v<typename detail::remove_cvref<R>::type> &&
              !detail::is_std_array_v<typename detail::remove_cvref<R>::type>,
          int> = 0>
  constexpr span(R &&r) : base_(r.data(), static_cast<size_type>(r.size())) {
    if constexpr (extent != dynamic_extent) {
      LVIZ_UTIL_SPAN_EXPECT(r.size() == extent,
                            "Cannot construct span with static extent");
    }
  }

  template <
      class U, size_type N,
      typename std::enable_if_t<
          (Extent == dynamic_extent || N == dynamic_extent || Extent == N) &&
              std::is_convertible_v<U (*)[], element_type (*)[]>,
          int> = 0>
  constexpr span(const span<U, N> &source) noexcept
      : base_(source.data(), source.size()) {
    if constexpr (extent != dynamic_extent) {
      LVIZ_UTIL_SPAN_EXPECT(source.size() == extent,
                            "Cannot construct span with static extent");
    }
  }

  constexpr span(const span &other) noexcept = default;

  ~span() noexcept = default;

  span &operator=(const span &other) noexcept = default;

  [[nodiscard]] constexpr size_type size() const noexcept {
    return size_;
  }

  [[nodiscard]] constexpr size_type size_bytes() const noexcept {
    return size_ * sizeof(element_type);
  }

  [[nodiscard]] constexpr bool empty() const noexcept {
    return size_ == 0;
  }

  [[nodiscard]] constexpr reference operator[](size_type idx) const {
#ifndef NDEBUG
    LVIZ_UTIL_SPAN_EXPECT(idx < size_, "span subscript out of range");
#endif

    return data_[idx];
  }

  [[nodiscard]] constexpr reference front() const {
#ifndef NDEBUG
    LVIZ_UTIL_SPAN_EXPECT(!empty(), "front() called on empty span");
#endif

    return data_[0];
  }

  [[nodiscard]] constexpr reference back() const {
#ifndef NDEBUG
    LVIZ_UTIL_SPAN_EXPECT(!empty(), "back() called on empty span");
#endif

    return data_[size_ - 1];
  }

  [[nodiscard]] constexpr pointer data() const noexcept {
    return data_;
  }

  [[nodiscard]] constexpr iterator begin() const noexcept {
    return data_;
  }

  [[nodiscard]] constexpr iterator end() const noexcept {
    return data_ + size_;
  }

  [[nodiscard]] constexpr reverse_iterator rbegin() const noexcept {
    return std::reverse_iterator(end());
  }

  [[nodiscard]] constexpr reverse_iterator rend() const noexcept {
    return std::reverse_iterator(begin());
  }
};

template <class T, std::size_t N> span(T (&)[N]) -> span<T, N>;

template <class T, std::size_t N> span(std::array<T, N> &) -> span<T, N>;

template <class T, std::size_t N>
span(const std::array<T, N> &) -> span<const T, N>;

template <class R>
span(R &&)
    -> span<std::remove_reference_t<decltype(*std::data(std::declval<R &>()))>>;

} // namespace util
} // namespace lviz

#endif
