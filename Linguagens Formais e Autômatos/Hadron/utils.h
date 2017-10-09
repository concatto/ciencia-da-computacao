#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils
{
private:
    Utils();

public:
    static void trim(std::string& s);
    static void rtrim(std::string& s);
    static void ltrim(std::string& s);
    static std::vector<std::string> split(const std::string& s, char delim);
};

#endif // UTILS_H
