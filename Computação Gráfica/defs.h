#include <stdint.h>
#include <utility>
#include <vector>

#define PI 3.14159265359

template <class T>
using Mapper = std::function<T(const T&)>;

template <class T>
using Consumer = std::function<void(const T&)>;

using ubyte = uint8_t;
using IntPair = std::pair<int, int>;

template <class T>
using Matrix = std::vector<std::vector<T>>;