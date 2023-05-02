#pragma once
#include <cstddef>

namespace itm {

template <std::size_t /* Index */, typename Type> struct IndexedItem {
  [[no_unique_address]] Type value;
};

} // namespace itm
