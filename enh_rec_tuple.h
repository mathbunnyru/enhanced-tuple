#pragma once
#include <cstddef>
#include <utility>

namespace enh_rec {

template <typename... Types> struct Tuple;

namespace impl {

template <std::size_t /* RestArgsNum */, typename Type> struct IndexedItem {
  Type value;
};

template <size_t Index> struct GetterByIndex {
  template <typename Type>
  static constexpr const Type &
  get_reference(const IndexedItem<Index, Type> &itm) {
    return itm.value;
  }

  template <typename Type>
  static constexpr Type &get_reference(IndexedItem<Index, Type> &itm) {
    return itm.value;
  }
};

template <typename Type> struct GetterByType {
  template <size_t Index>
  static constexpr const Type &
  get_reference(const IndexedItem<Index, Type> &itm) {
    return itm.value;
  }

  template <size_t Index>
  static constexpr Type &get_reference(IndexedItem<Index, Type> &itm) {
    return itm.value;
  }
};

} // namespace impl

template <> struct Tuple<> {};

template <typename Head, typename... Tail>
struct Tuple<Head, Tail...> : public impl::IndexedItem<sizeof...(Tail), Head>,
                              Tuple<Tail...> {
  Tuple(Head head, Tail... tail)
      : impl::IndexedItem<sizeof...(Tail), Head>{head},
        Tuple<Tail...>(tail...) {}

  Tuple() : impl::IndexedItem<sizeof...(Tail), Head>(), Tuple<Tail...>() {}
};

template <typename... Types> Tuple(Types...) -> Tuple<Types...>;

} // namespace enh_rec

namespace std {

template <class... Types> struct tuple_size<enh_rec::Tuple<Types...>> {
  static constexpr auto value = sizeof...(Types);
};

template <size_t index, typename... Types>
constexpr const auto &get(const enh_rec::Tuple<Types...> &t) {
  return enh_rec::impl::GetterByIndex<sizeof...(Types) - 1 -
                                      index>::get_reference(t);
}

template <size_t index, typename... Types>
constexpr auto &get(enh_rec::Tuple<Types...> &t) {
  return enh_rec::impl::GetterByIndex<sizeof...(Types) - 1 -
                                      index>::get_reference(t);
}

template <typename Type, typename... Types>
constexpr const auto &get(const enh_rec::Tuple<Types...> &t) {
  return enh_rec::impl::GetterByType<Type>::get_reference(t);
}

template <typename Type, typename... Types>
constexpr auto &get(enh_rec::Tuple<Types...> &t) {
  return enh_rec::impl::GetterByType<Type>::get_reference(t);
}

} // namespace std
