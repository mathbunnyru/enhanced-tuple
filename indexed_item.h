#pragma once
#include <cstddef>
#include <memory>

namespace itm {

template <std::size_t /* Index */, typename Type> struct IndexedItem {
  [[no_unique_address]] Type value{};
};

template <std::size_t Index, typename Type> struct IndexedItem<Index, Type &> {
  Type &value;

  IndexedItem(Type &val) : value(val) {}

  constexpr IndexedItem(const IndexedItem &) = default;
  constexpr IndexedItem(IndexedItem &&) = default;

  constexpr IndexedItem &operator=(const IndexedItem &rhs) {
    value = rhs.value;
    return *this;
  }

  constexpr IndexedItem &operator=(IndexedItem &&rhs) {
    value = std::move(rhs.value);
    return *this;
  }
};

} // namespace itm
