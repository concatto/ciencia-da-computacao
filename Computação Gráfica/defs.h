#include <stdint.h>

template <class T>
using Mapper = std::function<T(const T&)>;

using ubyte = uint8_t;