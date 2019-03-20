#include <stdint.h>

template <class T>
using Mapper = std::function<T(const T&)>;

template <class T>
using Consumer = std::function<void(const T&)>;

using ubyte = uint8_t;