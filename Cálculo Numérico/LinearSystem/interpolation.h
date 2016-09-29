#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "linearsystem.h"
#include "definitions.h"
#include <vector>
#include <functional>
#include <utility>
#include <string>

enum Axis {X, Y};
struct Point {
    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {}
};

Solution polynomialInterpolation(std::vector<Point> points, std::function<Solution(const Matrix&)> solver);
Solution linearInterpolation(const Point& a, const Point& b);
double lagrange(const std::vector<Point>& points, double x);

std::string toFunctionString(Solution solution);
std::vector<Point> reshapePoints(const std::vector<Point>& points);
void sortPoints(std::vector<Point> &points, Axis axis = Axis::X, bool crescent = true);

#endif // INTERPOLATION_H
