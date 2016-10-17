#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <vector>

using Row = std::vector<double>;
using Solution = std::vector<double>;
using Matrix = std::vector<Row>;
using uint = unsigned int;
enum IterativeMode { GaussJacobi, GaussSeidel };
enum Axis {X, Y};

struct Point {
    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {}
};

template <typename T>
Row operator*(const Row& row, T c) {
    Row r;
    for (T v : row) {
        r.push_back(v * c);
    }
    return r;
}

#endif // DEFINITIONS_H

