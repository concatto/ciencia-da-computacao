#include <iostream>
#include <cstdlib>

std::string calculateMantissa(unsigned value) {

}

int main() {
    std::string input = "10,5";
    int a = std::atoi(input.substr(0, input.find_first_of(',')).c_str());
    int b = std::atoi(input.substr(input.find_first_of(',') + 1).c_str());

    std::cout << a << " ; " << b << "\n";

}
