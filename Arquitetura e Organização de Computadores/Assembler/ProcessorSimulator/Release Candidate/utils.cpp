#include "utils.h"
#include <sstream>

Utils::Utils()
{

}

std::string Utils::toHexString(unsigned int word)
{
    std::stringstream stream;
    stream << "0x";
    for (int i = 1; i <= 8; i++) {
        stream << std::hex << ((word >> (32 - (i * 4))) & 0xF);
    }
    return stream.str();
}
