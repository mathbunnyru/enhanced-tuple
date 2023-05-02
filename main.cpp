#include "inh_tuple.h"
#include <iostream>
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
  TupleType<int &, double &> ref_t(i, j);
  std::get<0>(ref_t) = 100;
  std::get<double &>(ref_t) = 0.7;
  std::cout << i << ' ' << j << '\n';

  TupleType<Empty, Empty2, Empty, Empty, Empty2> empty{
      Empty{}, Empty2{}, Empty{}, Empty{}, Empty2{}};
  std::cout << sizeof(empty) << '\n';

  std::cout << sizeof(TupleType<Packed, char, Packed, char>) << '\n';

  TupleType<int> not_initialized;
  std::cout << std::get<int>(not_initialized) << '\n';

  int x = 5;
  int y = 10;
  TupleType<int &> ref_x(x);
  TupleType<int &> ref_y(y);
  ref_x = ref_y;
  std::get<int &>(ref_y) = 100;
  std::cout << x << ' ' << y << '\n';
}

int main() {
  test_tuple<std::tuple>("std::tuple");

  test_tuple<inh::Tuple>("inh::Tuple");
}
