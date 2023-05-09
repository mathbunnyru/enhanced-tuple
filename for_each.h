#pragma once
#include <cstddef>
#include <tuple>
#include <utility>

namespace impl {
template <typename TupleLike, typename Func, size_t... Idx>
void for_each(TupleLike&& t, Func&& f, std::index_sequence<Idx...>) {
  (f(get<Idx>(t)), ...);
}
} // namespace impl

template <typename TupleLike, typename Func>
void for_each(TupleLike&& t, Func&& f) {
  constexpr size_t TupleSize =
      std::tuple_size_v<std::remove_reference_t<TupleLike>>;
  impl::for_each(std::forward<TupleLike>(t), std::forward<Func>(f),
                 std::make_index_sequence<TupleSize>{});
}
