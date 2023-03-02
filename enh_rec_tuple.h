#pragma once
#include <tuple>
#include <cstddef>

namespace enh_rec {

template <typename... Types>
struct Tuple;

namespace impl {

template<typename ItemType, std::size_t /* RestArgsNum */>
struct IndexedItem {
  ItemType value;
};

template<size_t Index>
struct GetterByIndex {
  template <typename T>
  static constexpr const T& get_reference(const IndexedItem<T, Index>& itm) { return itm.value; }

  template <typename T>
  static constexpr T& get_reference(IndexedItem<T, Index>& itm) { return itm.value; }
};

}  // impl

template<>
struct Tuple<> {
};

template<typename Head, typename... Tail>
struct Tuple<Head, Tail...>: public impl::IndexedItem<Head, sizeof...(Tail)>, Tuple<Tail...> {
  Tuple(Head head, Tail... tail) :
      impl::IndexedItem<Head, sizeof...(Tail)>{head},
      Tuple<Tail...>(tail...) {}

  Tuple() :
      impl::IndexedItem<Head, sizeof...(Tail)>(),
      Tuple<Tail...>() {}
};

template <typename ...Types>
Tuple(Types...) -> Tuple<Types...>;

}  // enh_rec

namespace std {

template<class... Types>
struct tuple_size<enh_rec::Tuple<Types...>> {
static constexpr auto value = sizeof...(Types);
};

template<size_t index, typename... Types>
constexpr const auto& get(const enh_rec::Tuple<Types...>& t) {
  return enh_rec::impl::GetterByIndex<sizeof...(Types) - 1 - index>::get_reference(t);
}

template<size_t index, typename... Types>
constexpr auto& get(enh_rec::Tuple<Types...>& t) {
  return enh_rec::impl::GetterByIndex<sizeof...(Types) - 1 - index>::get_reference(t);
}

}  // std
