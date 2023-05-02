#pragma once
#include <cstddef>
#include <memory>

namespace itm {

template <std::size_t /* Index */, typename Type> struct IndexedItem {
  [[no_unique_address]] Type value{};
};

template <std::size_t Index, typename Type> struct IndexedItem<Index, Type &> {
  Type &value;

  IndexedItem(const IndexedItem &) = default;
  IndexedItem(IndexedItem &&) = default;

  IndexedItem &operator=(const IndexedItem &rhs) {
    value = rhs.value;
    return *this;
  }

  IndexedItem &operator=(IndexedItem &&rhs) {
    value = std::move(rhs.value);
    return *this;
  }
};

} // namespace itm
