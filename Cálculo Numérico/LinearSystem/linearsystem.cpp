#include "linearsystem.h"

#include <cmath>
#include <limits>
#include <algorithm>

const double Minimum = 1E-11;

void printRow(const Row& row, std::ostream& out) {
    for (const double d : row) {
        out << d << "    ";
    }
    out << "\n";
}

void printMatrix(const Matrix& m, std::ostream& out) {
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

SystemType classifySystem(const Matrix& matrix) {
    const Row& lastRow = matrix.back();

    //TODO: Testar NaN

    double lastRowSum = 0;
    for (uint i = 0; i < lastRow.size() - 1; i++) {
        lastRowSum += lastRow[i];
    }

    if (lastRowSum == 0) {
        return lastRow.back() == 0 ? SystemType::Indeterminate : SystemType::Impossible;
    } else {
        if (lastRow.back() == lastRow[lastRow.size() - 2]) {
            return SystemType::Indeterminate;
        }
    }

    return SystemType::Possible;
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

Solution solveSystem(const Matrix& problem, bool usePartialPivot) {
    Matrix matrix = gaussianElimination(problem, usePartialPivot);

    SystemType type = classifySystem(matrix);
    if (type != SystemType::Possible) {
        std::cout << (type == SystemType::Impossible ? "Impossível" : "Indeterminado") << "\n";
        return Row(matrix.size(), NAN);
    }

    Solution solution(matrix.size(), 0);

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

double errorFunction(const Solution &currentSolution, const Solution &previousSolution) {
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

Solution solveSystemIteratively(const Matrix& matrix, double precision, bool improvedMode, Solution previousSolution) {
    if (previousSolution.empty()) {
        previousSolution = Row(matrix.size(), 0);
    }

    Solution solution(matrix.size(), 0);

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

bool testSassenfeldCriterion(const Matrix& matrix) {
    std::vector<double> beta(matrix.size(), 1);
    for (uint i = 0; i < beta.size(); i++) {
        double sum = 0;
        for (uint j = 0; j < matrix[i].size() - 1; j++) {
            if (i == j) continue;

            sum += std::abs(matrix[i][j]) * beta[j];
        }

        beta[i] = sum / matrix[i][i];

        std::cout << "beta " << i << " = " << sum << " / " << matrix[i][i] << "\n";
    }

    return std::all_of(beta.begin(), beta.end(), [](double v) { return v < 1; });
}

bool testRowsColumnsCriterion(const Matrix& matrix) {
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

bool hasSolution(const Matrix& matrix) {
    return testRowsColumnsCriterion(matrix) || testSassenfeldCriterion(matrix);
}

void verifySolution(const Solution &solution, const Matrix& matrix, std::ostream& out) {
    for (uint i = 0; i < matrix.size(); i++) {
        double sum = 0;
        for (uint j = 0; j < matrix[i].size() - 1; j++) {
            sum += matrix[i][j] * solution[j];
        }

        out << "Delta: " << (sum - matrix[i].back()) << "\n";
    }
}
