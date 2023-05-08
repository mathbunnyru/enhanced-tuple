#include "inh_tuple.h"
#include <iostream>
#include <memory>
#include <string_view>
#include <tuple>

struct S {
  int num;
};

struct Empty {};

struct Empty2 {};

#pragma pack(push, 1)

struct Packed {
  char arr[6];
  uint64_t num;
  char some_char;
};

#pragma pack(pop)

static_assert(sizeof(Packed) == 15);

template <template <typename... Types> class TupleType>
void test_tuple(std::string_view description) {
  std::cout << std::string(40, '=') << "\ntesting: " << description << '\n';

  TupleType<int, double, S> simple_t(0, 1.5, S{20});
  std::get<2>(simple_t).num = 200;
  std::cout << std::get<2>(simple_t).num << '\n';
  std::cout << std::get<int>(simple_t) << '\n';

  int i = 10;
  double j = 0.5;
  TupleType<int&, double&> ref_t(i, j);
  std::get<0>(ref_t) = 100;
  std::get<double&>(ref_t) = 0.7;
  std::cout << i << ' ' << j << '\n';

  TupleType<Empty, Empty2, Empty, Empty, Empty2> almost_empty{
      Empty{}, Empty2{}, Empty{}, Empty{}, Empty2{}};
  std::cout << sizeof(almost_empty) << '\n';

  std::cout << sizeof(TupleType<Packed, char, Packed, char>) << '\n';

  TupleType<int> not_initialized;
  std::cout << std::get<int>(not_initialized) << '\n';

  int x = 5;
  int y = 10;
  int z = 20;
  TupleType<int&, int> ref_x(x, z);
  TupleType<int&, int> ref_y(y, z);
  ref_x = ref_y;
  std::get<int&>(ref_y) = 100;
  std::cout << x << ' ' << y << '\n';

  TupleType<> empty;
  std::cout << std::tuple_size_v<decltype(empty)> << '\n';

  TupleType<> empty_init{};
  std::cout << std::tuple_size_v<decltype(empty_init)> << '\n';

  TupleType deducted_t(5, 3.5);
  std::cout << std::get<int>(deducted_t) << ' ' << std::get<double>(deducted_t)
            << '\n';

  TupleType<std::unique_ptr<int>> move_only_t(std::make_unique<int>(7));
  std::cout << *std::get<0>(move_only_t) << '\n';
}

int main() {
  test_tuple<std::tuple>("std::tuple");

  test_tuple<inh::Tuple>("inh::Tuple");
}
