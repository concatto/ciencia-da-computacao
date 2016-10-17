#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "definitions.h"
#include <vector>
#include <functional>
#include <utility>
#include <string>

Solution polynomialInterpolation(std::vector<Point> points);
Solution polynomialInterpolation(std::vector<Point> points, std::function<Solution(const Matrix&)> solver);
Solution linearInterpolation(const Point& a, const Point& b);
double lagrange(const std::vector<Point>& points, double x);
Solution newtonPolynomial(const std::vector<Point>& points);
Matrix computeDividedDifferencesTable(const std::vector<Point>& points);

#endif // INTERPOLATION_H
