#include <iostream>
#include <vector>

using Row = std::vector<double>;
using Matrix = std::vector<Row>;
using uint = unsigned int;

Matrix gaussianElimination(Matrix m) {
    for (uint i = 0; i < m.size() - 1; i++) {
        double pivot = m[i][i];

        for (uint j = i + 1; j < m.size(); j++) {
            double multiplier = -m[j][i] / pivot;

            std::cout << "When i = " << i << " and j = " << j << ", multiplier = " << multiplier << "\n";

            for (uint k = 0; k < m[j].size(); k++) {
                m[j][k] = m[j][k] + (multiplier * m[i][k]);
            }
        }
    }

    return m;
}

void printMatrix(const Matrix& m, std::ostream& out) {
    for (const Row& row : m) {
        for (const double d : row) {
            out << d << "    ";
        }
        out << "\n";
    }
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

    printMatrix(gaussianElimination(m2), std::cout);

}

