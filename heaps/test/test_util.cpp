#include "test_util.h"
#include <random>

std::vector<Key> random_keys(bool monotone, size_t count, Key min, Key max, int seed) {
    std::vector<Key> keys (count);

    if (monotone){
        keys[0] = min;
    }

    std::default_random_engine engine (seed);
    std::uniform_int_distribution<Key> distribution(min, max);
    distribution(engine); //first value always 0 ?!

    for (size_t i = (size_t)monotone; i < count; ++i){
        keys[i] = distribution(engine);
    }

    return keys;
}

