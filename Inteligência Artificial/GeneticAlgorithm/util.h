#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>

double aleatorio() {
    return std::rand() / static_cast<double>(RAND_MAX);
}

#endif // UTIL_H
