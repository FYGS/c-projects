#include <cassert>
#include "reciprocal.hpp"

double reciprocal(int i) {
  // i doit être différent de 0
  assert(i != 0);

  return 1.0 / i;
}