#include "linearsystem.h"

#include <cmath>
#include <algorithm>
#include "utils.h"

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

//Matrix must be in row echelon form
SystemType classifySystem(const Matrix& matrix) {
    for (Matrix::const_reverse_iterator it = matrix.rbegin(); it != matrix.rend(); ++it) {
        const Row& row = *it;
        bool nonZeroRow = std::any_of(row.begin(), row.end(), [](double v) { return v != 0; });

        if (nonZeroRow) {
            //Only nonzero value is in the B vector
            if (std::all_of(row.begin(), row.end() - 1, [](double v) { return v == 0; })) {
                return SystemType::Impossible;
            }

            break;
        }
    }

    uint prevZeros = 0;
    for (const Row& row : matrix) {
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
    Matrix matrix = gaussianElimination(problem, usePartialPivot);
    printMatrix(matrix);

    SystemType type = classifySystem(matrix);
    if (type != SystemType::Possible) {
        std::cout << (type == SystemType::Impossible ? "Impossivel" : "Possivel indeterminado") << "\n";
        return Row(matrix.size(), NAN);
    }

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

    return numerator / denominator;
}

Solution solveSystemIteratively(const Matrix& matrix, double precision, IterativeMode mode, Solution previousSolution) {
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

                if (mode == IterativeMode::GaussSeidel) {
                    m -= matrix[i][j] * (i < j ? previousSolution[j] : solution[j]);
                } else if (mode == IterativeMode::GaussJacobi) {
                    m -= matrix[i][j] * previousSolution[j];
                }
            }

            solution[i] *= m;
        }

        std::cout << "Current iteration -> ";
        printRow(solution);

        error = errorFunction(solution, previousSolution);
        std::cout << "Error: " << error << "\n";
        previousSolution = solution;
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

        if (matrix[i][i] == 0) {
            std::cout << "Division by zero! Can't test Sassenfeld!\n";
            return false;
        }

        beta[i] = sum / matrix[i][i];

        std::cout << "Beta " << i << " = " << sum << " / " << matrix[i][i] << " = " << beta[i] << "\n";
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

            sumRow  += matrix[i][j];
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
    if (std::any_of(solution.begin(), solution.end(), [](double v) { return std::isnan(v); })) {
        std::cout << "Solution contains NaN! Stopping...\n";
        return;
    }

    for (uint i = 0; i < matrix.size(); i++) {
        double sum = 0;
        for (uint j = 0; j < matrix[i].size() - 1; j++) {
            sum += matrix[i][j] * solution[j];
        }

        out << "Output: " << sum << "\n";
        out << "Target: " << matrix[i].back() << "\n";
        out << "Delta: " << (sum - matrix[i].back()) << "\n";
        out << "\n";
    }
}
