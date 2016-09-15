#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using Row = std::vector<double>;
using Matrix = std::vector<Row>;
using uint = unsigned int;
const double Minimum = 1E-15; //1E-15

void printRow(const Row& row, std::ostream& out = std::cout) {
    for (const double d : row) {
        out << d << "    ";
    }
    out << "\n";
}

void printMatrix(const Matrix& m, std::ostream& out = std::cout) {
    for (const Row& row : m) {
        printRow(row, out);
    }
}

bool nearZero(double value) {
    return value < Minimum && value > (0 - Minimum);
}

void partialPivot(Matrix& m, uint rowIndex) {
    uint highestRow = rowIndex;
    double highestValue = m[rowIndex][rowIndex];
    for (uint i = rowIndex + 1; i < m.size(); i++) {
        if (std::abs(m[i][rowIndex]) > std::abs(highestValue)) {
            highestRow = i;
            highestValue = m[i][rowIndex];
        }
    }

    if (rowIndex != highestRow) {
        std::swap(m[rowIndex], m[highestRow]);
    }
}

Matrix gaussianElimination(Matrix m, bool usePartialPivot) {
    for (uint i = 0; i < m.size() - 1; i++) {
        if (usePartialPivot) {
            partialPivot(m, i);
        }

        double pivot = m[i][i];

        for (uint j = i + 1; j < m.size(); j++) {
            double multiplier = -m[j][i] / pivot;

            for (uint k = 0; k < m[j].size(); k++) {
                m[j][k] = m[j][k] + (multiplier * m[i][k]);

                if (nearZero(m[j][k])) {
                    m[j][k] = 0;
                }
            }
        }
    }

    return m;
}

Row solveSystem(const Matrix& problem, bool usePartialPivot = false) {
    Matrix matrix = gaussianElimination(problem, usePartialPivot);
    Row solution(matrix.size(), 0);

    for (int i = solution.size() - 1; i >= 0; i--) {
        double b = matrix[i].back();

        double sum = 0;
        for (uint j = i + 1; j < solution.size(); j++) { //Will not execute when i = |solution|
            sum += matrix[i][j] * solution[j];
        }

        solution[i] = (b - sum) / matrix[i][i];
    }

    return solution;
}

double errorFunction(const Row& currentSolution, const Row& previousSolution) {
    double numerator = std::numeric_limits<double>::min();
    double denominator = std::numeric_limits<double>::min();

    for (uint i = 0; i < currentSolution.size(); i++) {
        double value = std::abs(currentSolution[i] - previousSolution[i]);
        if (value > numerator) {
            numerator = value;
        }

        value = std::abs(currentSolution[i]);
        if (value > denominator) {
           denominator = value;
        }
    }

    return numerator / denominator;
}

Row solveSystemIteratively(const Matrix& matrix, Row previousSolution, double precision, bool improvedMode) {
    Row solution(matrix.size(), 0);

    double error;
    do {
        for (uint i = 0; i < solution.size(); i++) {
            solution[i] = (1 / matrix[i][i]);

            double m = matrix[i].back();

            for (uint j = 0; j < matrix[i].size() - 1; j++) {
                if (j == i) continue;

                if (improvedMode) {
                    m -= matrix[i][j] * (i < j ? previousSolution[j] : solution[j]);
                } else {
                    m -= matrix[i][j] * previousSolution[j];
                }
            }

            solution[i] *= m;
        }

        error = errorFunction(solution, previousSolution);
        std::cout << "Error: " << error << "\n";
        previousSolution = solution;
        printRow(solution);
    } while (error > precision);

    return solution;
}

bool hasSolution(const Matrix& matrix) {
    for (uint i = 0; i < matrix.size(); i++) {
        double sumRow = 0;
        double sumColumn = 0;
        for (uint j = 0; j < matrix[i].size(); j++) {
            if (i == j) continue;
            if (j >= matrix.size()) break;

            sumRow += matrix[i][j];
            sumColumn += matrix[j][i];
        }

        if ((sumRow / matrix[i][i] >= 1) && (sumColumn / matrix[i][i] >= 1)) {
            return false;
        }
    }

    return true;
}

int main()
{
    Matrix m = {
        {2, 2, 1, 1, 7},
        {1, -1, 2, -1, 1},
        {3, 2, -3, -2, 4},
        {4, 3, 2, 1, 12}
    };

    Matrix m2 = {
        {3, 2, 4, 1},
        {1, 1, 2, 2},
        {4, 3, -2, 3}
    };

    Matrix m3 = {
        {2, 1, 7, 4, -3, -1, 4, 4, 7, 0, 86},
        {4, 2, 2, 3, -2, 0, 3, 3, 4, 1, 45},
        {3, 4, 4, 2, 1, -2, 2, 1, 9, -3, 52.5},
        {9, 3, 5, 1, 0, 5, 6, -5, -3, 4, 108},
        {2, 0, 7, 0, -5, 7, 1, 0, 1, 6, 66.5},
        {1, 9, 8, 0, 3, 9, 9, 0, 0, 5, 90.5},
        {4, 1, 9, 0, 4, 3, 7, -4, 1, 3, 139},
        {6, 3, 1, 1, 6, 8, 3, 3, 0, 2, 61},
        {6, 5, 0, -7, 7, -7, 6, 2, -6, 1, -43.5},
        {1, 6, 3, 4, 8, 3, -5, 0, -6, 0, 31}
    };

    Matrix m4 = {
        {2, 1, 3, 1},
        {2, 6, 8, 3},
        {6, 8, 18, 5}
    };

    Matrix m5 = {
        {6, 2, -1, 7},
        {2, 4, 1, 7},
        {3, 2, 8, 13}
    };

    Matrix m6 = {
        {10, 2, 1, 7},
        {1, 5, 1, -8},
        {2, 3, 10, 6}
    };

    Matrix m7 = {
        {10, 3, -2, 57},
        {2, 8, -1, 20},
        {1, 1, 5, -4}
    };

    Matrix m8 = {
        {4, -1, 0, -1, 0, 0, 0, 0, 0, 0, -110},
        {-1, 4, -1, 0, -1, 0, 0, 0, 0, 0, -30},
        {0, -1, 4, 0, 0, -1, 0, 0, 0, 0, -40},
        {-1, 0, 0, 4, -1, 0, 0, 0, 0, 0, -110},
        {0, -1, 0, -1, 4, -1, -1, 0, 0, 0, 0},
        {0, 0, -1, 0, -1, 4, 0, -1, 0, 0, -15},
        {0, 0, 0, 0, -1, 0, 4, -1, 0, 0, -90},
        {0, 0, 0, 0, 0, -1, -1, 4, -1, 0, -25},
        {0, 0, 0, 0, 0, 0, 0, -1, 4, -1, -55},
        {0, 0, 0, 0, 0, 0, 0, 0, -1, 4, -65}
    };

    Row solution = solveSystemIteratively(m7, {0, 0, 0}, 1E-5, false);
    printRow(solution);

    //Matrix result = gaussianElimination(m8, true);
    //printRow(solveSystem(result));

    //hasSolution(m6);
}

