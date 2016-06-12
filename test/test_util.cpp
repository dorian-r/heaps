#include "test_util.h"
#include <random>

std::vector<Key> random_keys(size_t count, Key min, Key max, int seed) {
    std::vector<Key> keys (count);

    std::default_random_engine engine (seed);
    std::uniform_int_distribution<Key> distribution(min, max);

    for (size_t i = 0; i < count; ++i){
        keys[i] = distribution(engine);
    }

    return keys;
}