#include "linearsystem.h"

#include <cmath>
#include <algorithm>
#include <fstream>
#include "utils.h"

void partialPivot(Matrix& m, uint rowIndex, uint columnIndex) {
    uint highestRow = rowIndex;
    double highestValue = m[rowIndex][columnIndex];
    for (uint i = rowIndex + 1; i < m.size(); i++) {
        if (std::abs(m[i][columnIndex]) > std::abs(highestValue)) {
            highestRow = i;
            highestValue = m[i][columnIndex];
        }
    }

    if (rowIndex != highestRow) {
        std::swap(m[rowIndex], m[highestRow]);
    }
}

void partialPivot(Matrix &m, uint rowIndex) {
    partialPivot(m, rowIndex, rowIndex);
}

Matrix gaussianEliminationClassification(Matrix m) {
    for (uint i = 0; i < m.size() - 1; i++) {
        uint col = i;
        for (uint j = i; j < m[i].size(); j++) {
            if (m[i][j] != 0) {
                col = j;
                break;
            }
        }

        partialPivot(m, i, col);
        double pivot = m[i][col];

        if (pivot == 0) {
            continue;
        }

        for (uint j = i + 1; j < m.size(); j++) {
            double multiplier = -m[j][col] / pivot;

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

SystemType classifySystem(const Matrix& matrix) {
    Matrix echelon = gaussianEliminationClassification(matrix);

    for (Matrix::const_reverse_iterator it = echelon.rbegin(); it != echelon.rend(); ++it) {
        const Row& row = *it;
        bool nonZeroRow = std::any_of(row.begin(), row.end(), [](double v) { return v != 0; });

        if (nonZeroRow) {
            //Only nonzero value is in the B vector
            if (std::all_of(row.begin(), row.end() - 1, [](double v) { return v == 0; })) {
                printMatrix(echelon);
                return SystemType::Impossible;
            }

            break;
        }
    }

    uint prevZeros = 0;
    for (const Row& row : echelon) {
        uint zeros = 0;

        for (double v : row) {
            if (v == 0) {
                zeros++;
            } else {
                break;
            }
        }

        //Not perfectly triangular
        if (std::abs(zeros - prevZeros) > 1) {
            printMatrix(echelon);
            return SystemType::Indeterminate;
        }

        prevZeros = zeros;
    }

    return SystemType::Possible;
}

Matrix gaussianElimination(Matrix m, bool usePartialPivot) {
    for (uint i = 0; i < m.size() - 1; i++) {
        if (usePartialPivot) {
            partialPivot(m, i);
        }

        double pivot = m[i][i];

        if (pivot == 0) {
            if (usePartialPivot) {
                continue;
            } else {
                std::cout << "Pivot is zero! Stopping...\n";
                return Matrix(m.size(), Row(m.front().size(), NAN));
            }
        }

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
    SystemType type = classifySystem(problem);

    if (type != SystemType::Possible) {
        std::cout << (type == SystemType::Impossible ? "Impossivel" : "Possivel indeterminado") << "\n";
        return Row(problem.size(), NAN);
    } else {
        std::cout << "Possivel\n";
    }

    Matrix matrix = gaussianElimination(problem, usePartialPivot);
    printMatrix(matrix);    

    Solution solution(matrix.size(), 0);

    for (int i = solution.size() - 1; i >= 0; i--) {
        double b = matrix[i].back();

        double sum = 0;
        for (uint j = i + 1; j < solution.size(); j++) {
            sum += matrix[i][j] * solution[j];
        }

        solution[i] = (b - sum) / matrix[i][i];
    }

    return solution;
}

double errorFunction(const Solution &currentSolution, const Solution &previousSolution) {
    double numerator = std::abs(currentSolution[0] - previousSolution[0]);
    double denominator = std::abs(currentSolution[0]);

    for (uint i = 1; i < currentSolution.size(); i++) {
        double value = std::abs(currentSolution[i] - previousSolution[i]);
        if (value > numerator) {
            numerator = value;
        }

        value = std::abs(currentSolution[i]);
        if (value > denominator) {
           denominator = value;
        }
    }

    std::cout << "Epsilon = " << numerator << " / " << denominator << "\n";
    return numerator / denominator;
}

Solution solveSystemIteratively(const Matrix& matrix, double precision, IterativeMode mode, Solution previousSolution) {
    if (previousSolution.empty()) {
        previousSolution = Row(matrix.size(), 0);
    }

    Solution solution(matrix.size(), 0);

    uint k = 1;
    double error;
    std::cout.precision(10);
    do {
        for (uint i = 0; i < solution.size(); i++) {
            solution[i] = (1 / matrix[i][i]);

            double m = matrix[i].back();

            for (uint j = 0; j < matrix[i].size() - 1; j++) {
                if (j == i || matrix[i][j] == 0) continue;

                if (mode == IterativeMode::GaussSeidel) {
                    m -= matrix[i][j] * (i < j ? previousSolution[j] : solution[j]);
                } else if (mode == IterativeMode::GaussJacobi) {
                    m -= matrix[i][j] * previousSolution[j];
                }
            }

            solution[i] *= m;
        }

        std::cout << "Current iteration (" << k << ") -> ";
        printRow(solution);

        error = errorFunction(solution, previousSolution);
        std::cout << "Error: " << error << "\n";

        verifySolution(solution, matrix);
        previousSolution = solution;
        k++;
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

        std::cout << "Beta " << i << " = " << sum << " / " << matrix[i][i] << " = ";
        if (matrix[i][i] == 0) {
            std::cout << "Division by zero! Can't test Sassenfeld!\n";
            return false;
        }

        beta[i] = sum / std::abs(matrix[i][i]);
        std::cout << beta[i] << "\n";
    }

    if (std::all_of(beta.begin(), beta.end(), [](double v) { return v < 1; })) {
        std::cout << "Passed Sassenfeld\n";
        return true;
    }
    std::cout << "Didn't pass Sassenfeld\n";
    return false;
}

bool testRowsColumnsCriterion(const Matrix& matrix) {
    for (uint i = 0; i < matrix.size(); i++) {
        double sumRow = 0;
        double sumColumn = 0;
        for (uint j = 0; j < matrix[i].size(); j++) {
            if (i == j) continue;
            if (j >= matrix.size()) break;

            sumRow += std::abs(matrix[i][j]);
            sumColumn += std::abs(matrix[j][i]);
        }

        if ((sumRow / std::abs(matrix[i][i]) >= 1) && (sumColumn / std::abs(matrix[i][i]) >= 1)) {
            return false;
        }
    }

    return true;
}

bool hasSolution(const Matrix& matrix) {
    return testRowsColumnsCriterion(matrix) || testSassenfeldCriterion(matrix);
}

void verifySolution(const Solution &solution, const Matrix& matrix, std::ostream& out) {
    if (std::any_of(solution.begin(), solution.end(), [](double v) { return std::isnan(v); })) {
        std::cout << "Solution contains NaN! Stopping...\n";
        return;
    }

    Row result = matrix * solution;

    for (uint i = 0; i < result.size(); i++) {
        out << "Output: " << result[i] << "\n";
        out << "Target: " << matrix[i].back() << "\n";
        out << "Delta: " << (result[i] - matrix[i].back()) << "\n";
        out << "\n";
    }
}
