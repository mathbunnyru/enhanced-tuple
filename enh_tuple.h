#pragma once
#include <cstddef>
#include <tuple>

namespace enh_inh {

template <typename... Types> struct Tuple;

namespace impl {

template <std::size_t /* Index */, typename Type> struct IndexedItem {
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

template <typename, typename...> struct TupleBase;

template <std::size_t... Is, typename... Types>
struct TupleBase<std::index_sequence<Is...>, Types...>
    : IndexedItem<Is, Types>... {
  template <typename... Us>
  TupleBase(Us... us) : IndexedItem<Is, Types>{us}... {}
};

} // namespace impl

template <> struct Tuple<> {};

template <typename... Types>
struct Tuple
    : public impl::TupleBase<std::make_index_sequence<sizeof...(Types)>,
                             Types...> {
  Tuple(const Types &...items)
      : impl::TupleBase<std::make_index_sequence<sizeof...(Types)>, Types...>(
            items...) {}
};

template <typename... Types> Tuple(Types...) -> Tuple<Types...>;

} // namespace enh_inh

namespace std {

template <class... Types> struct tuple_size<enh_inh::Tuple<Types...>> {
  static constexpr auto value = sizeof...(Types);
};

template <size_t index, typename... Types>
constexpr const auto &get(const enh_inh::Tuple<Types...> &t) {
  return enh_inh::impl::GetterByIndex<index>::get_reference(t);
}

template <size_t index, typename... Types>
constexpr auto &get(enh_inh::Tuple<Types...> &t) {
  return enh_inh::impl::GetterByIndex<index>::get_reference(t);
}

} // namespace std
