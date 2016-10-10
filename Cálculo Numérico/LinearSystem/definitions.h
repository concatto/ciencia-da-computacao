#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <vector>

using Row = std::vector<double>;
using Solution = std::vector<double>;
using Matrix = std::vector<Row>;
using uint = unsigned int;
enum IterativeMode { GaussJacobi, GaussSeidel };

#endif // DEFINITIONS_H

