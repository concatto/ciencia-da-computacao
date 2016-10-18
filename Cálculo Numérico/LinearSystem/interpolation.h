#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "definitions.h"
#include <vector>
#include <iostream>
#include <functional>
#include <utility>
#include <string>

Solution polynomialInterpolation(std::vector<Point> points);
Solution polynomialInterpolation(std::vector<Point> points, std::function<Solution(const Matrix&)> solver);
Solution linearInterpolation(const Point& a, const Point& b);
double lagrange(const std::vector<Point>& points, double x);
Solution newtonPolynomial(const std::vector<Point>& points);
Matrix computeDividedDifferencesTable(const std::vector<Point>& points);

void verifySolution(const Solution& solution, const std::vector<Point>& points, std::ostream& out = std::cout);

#endif // INTERPOLATION_H
