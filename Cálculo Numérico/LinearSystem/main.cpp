#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using Row = std::vector<double>;
using Matrix = std::vector<Row>;
using uint = unsigned int;
const double Minimum = 0.000000000000001; //1E-15

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

Matrix gaussianElimination(Matrix m, bool usePartialPivot = false) {
    for (uint i = 0; i < m.size() - 1; i++) {
        if (usePartialPivot) {
            partialPivot(m, i);
        }

        double pivot = m[i][i];
        //std::cout << "Pivot for " << i << " = " << pivot << "\n";

        for (uint j = i + 1; j < m.size(); j++) {
            double multiplier = -m[j][i] / pivot;

            //std::cout << "When i = " << i << " and j = " << j << ", multiplier = " << multiplier << "\n";

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

Row solveSystem(const Matrix& matrix) {
    Row solution(matrix.size(), 0);

    for (int i = solution.size() - 1; i >= 0; i--) {
        double b = matrix[i].back();

        double sum = 0;
        for (uint j = i + 1; j < solution.size(); j++) { //Will not run when i = |solution|
            sum += matrix[i][j] * solution[j];
        }

        solution[i] = (b - sum) / matrix[i][i];
    }

    return solution;
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

    Matrix result = gaussianElimination(m5, true);
    printMatrix(result, std::cout);
    printRow(solveSystem(result), std::cout);

}

