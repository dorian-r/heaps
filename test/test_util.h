#ifndef HEAPS_TEST_UTIL_H
#define HEAPS_TEST_UTIL_H

#include "util.h"
#include <vector>
#include <limits>

std::vector<Key> random_keys(size_t count, Key min = 0, Key max = std::numeric_limits<Key>::max(), int seed = 0);

#endif //HEAPS_TEST_UTIL_H
