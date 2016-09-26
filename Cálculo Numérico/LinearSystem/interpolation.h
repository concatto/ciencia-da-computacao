#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "linearsystem.h"
#include "definitions.h"
#include <vector>
#include <functional>
#include <utility>
#include <string>

struct Point {
    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {}
};

Solution polynomialInterpolation(std::vector<Point> points, std::function<Solution(const Matrix&)> solver);
Solution linearInterpolation(const Point& a, const Point& b);
std::string toFunctionString(Solution solution);

#endif // INTERPOLATION_H
