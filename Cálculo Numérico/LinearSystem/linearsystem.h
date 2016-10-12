#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include "definitions.h"
#include <iostream>
#include <vector>

enum SystemType {
    Possible, Impossible, Indeterminate
};


void partialPivot(Matrix& m, uint rowIndex);
Matrix gaussianElimination(Matrix m, bool usePartialPivot);
Solution solveSystem(const Matrix& problem, bool usePartialPivot = false);
Solution solveSystemIteratively(const Matrix& matrix, double precision, IterativeMode mode, Solution previousSolution = Solution(0));

SystemType classifySystem(const Matrix& matrix);
double errorFunction(const Solution& currentSolution, const Solution& previousSolution);
bool testSassenfeldCriterion(const Matrix& matrix);
bool testRowsColumnsCriterion(const Matrix& matrix);
bool hasSolution(const Matrix& matrix);
void verifySolution(const Solution& solution, const Matrix& matrix, std::ostream& out = std::cout);

#endif // LINEARSYSTEM_H
