#ifndef UTILS_H
#define UTILS_H

#include "definitions.h"
#include <iostream>

void printRow(const Row& row, std::ostream& out = std::cout);
void printMatrix(const Matrix& m, std::ostream& out = std::cout);
bool nearZero(double value);
double applyFunction(const Solution& solution, double x);

std::string toFunctionString(Solution solution);
std::vector<Point> reshapePoints(const std::vector<Point>& points);
void sortPoints(std::vector<Point> &points, Axis axis = Axis::X, bool crescent = true);
Solution constructSimplePolynomial(const std::vector<double>& coefficients);
std::vector<std::vector<uint>> permutations(uint quantity);

#endif // UTILS_H
