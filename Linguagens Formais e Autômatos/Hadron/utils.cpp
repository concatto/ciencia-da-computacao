#include "utils.h"
#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>

Utils::Utils()
{

}

void Utils::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

void Utils::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void Utils::trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

std::vector<std::string> Utils::split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}
