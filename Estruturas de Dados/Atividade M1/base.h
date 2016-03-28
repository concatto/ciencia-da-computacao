#ifndef BASE_H
#define BASE_H

#include <random>
#include <ctime>

namespace SortMode {
    enum Type {Bubble, Merge};
}

class RandomNumberGenerator {
public:
    static int generate(int min, int max) {
        static std::default_random_engine engine(std::time(NULL));

        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(engine);
    }
};

#endif
