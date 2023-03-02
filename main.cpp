#include "enh_rec_tuple.h"
#include "enh_tuple.h"
#include <iostream>

struct S {
  int num;
};

int main() {
  enh_inh::Tuple<int, double, S> t(0, 1.5, S{20});
  std::cout << std::get<2>(t).num << "\n";

  enh_inh::Tuple auto_t(1, 2.5, S{30});
  std::cout << std::get<2>(auto_t).num << "\n";
}
