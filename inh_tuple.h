#pragma once
#include "indexed_item.h"
#include <cstddef>
#include <utility>

namespace inh {

template <typename... Types> struct Tuple;

namespace impl {

template <size_t Index> struct GetterByIndex {
  template <typename Type>
  static constexpr const Type&
  get_reference(const itm::IndexedItem<Index, Type>& itm) {
    return itm.value;
  }

  template <typename Type>
  static constexpr Type& get_reference(itm::IndexedItem<Index, Type>& itm) {
    return itm.value;
  }
};

template <typename Type> struct GetterByType {
  template <size_t Index>
  static constexpr const Type&
  get_reference(const itm::IndexedItem<Index, Type>& itm) {
    return itm.value;
  }

  template <size_t Index>
  static constexpr Type& get_reference(itm::IndexedItem<Index, Type>& itm) {
    return itm.value;
  }
};

template <typename, typename...> struct TupleBase;

template <std::size_t... Is, typename... Types>
class TupleBase<std::index_sequence<Is...>, Types...>
    : public itm::IndexedItem<Is, Types>... {
public:
  template <typename... Us>
  TupleBase(Us&&... us)
      : itm::IndexedItem<Is, Types>{std::forward<Us>(us)}... {}

  TupleBase() = default;
};

} // namespace impl

template <typename... Types>
class Tuple
    : public impl::TupleBase<std::index_sequence_for<Types...>, Types...> {
public:
  using TB = impl::TupleBase<std::index_sequence_for<Types...>, Types...>;
  using TB::TB;
};

template <typename... Types> Tuple(Types...) -> Tuple<Types...>;

template <size_t index, typename... Types>
constexpr const auto& get(const inh::Tuple<Types...>& t) {
  return inh::impl::GetterByIndex<index>::get_reference(t);
}

template <size_t index, typename... Types>
constexpr auto& get(inh::Tuple<Types...>& t) {
  return inh::impl::GetterByIndex<index>::get_reference(t);
}

template <typename Type, typename... Types>
constexpr const auto& get(const inh::Tuple<Types...>& t) {
  return inh::impl::GetterByType<Type>::get_reference(t);
}

template <typename Type, typename... Types>
constexpr auto& get(inh::Tuple<Types...>& t) {
  return inh::impl::GetterByType<Type>::get_reference(t);
}

} // namespace inh

template <class... Types> struct std::tuple_size<inh::Tuple<Types...>> {
  static constexpr auto value = sizeof...(Types);
};
