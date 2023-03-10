#include "enh_rec_tuple.h"
#include "enh_tuple.h"
#include <iostream>
#include <string_view>
#include <tuple>

struct S {
  int num;
};

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
}

int main() {
  test_tuple<std::tuple>("std::tuple");

  test_tuple<enh_inh::Tuple>("enh_inh::Tuple");

  test_tuple<enh_rec::Tuple>("enh_inh::Tuple");
}
