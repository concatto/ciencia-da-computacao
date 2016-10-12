#include "interpolation.h"

#include <cmath>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "linearsystem.h"
#include "utils.h"

Solution polynomialInterpolation(std::vector<Point> points) {
    return polynomialInterpolation(points, [](const Matrix& m) {
        //By default, solve using Gaussian Elimination with partial pivoting.
        return solveSystem(m, true);
    });
}

Solution polynomialInterpolation(std::vector<Point> points, std::function<Solution(const Matrix&)> solver) {
    Matrix matrix;

    for (uint i = 0; i < points.size(); i++) {
        Row row;

        for (uint j = 0; j < points.size(); j++) {
            //x^0, x^1, x^2, ...
            row.push_back(std::pow(points[i].x, j));
        }

        row.push_back(points[i].y);
        matrix.push_back(row);
    }

    return solver(matrix);
}

Solution linearInterpolation(const Point &a, const Point &b) {
    double c = (b.y - a.y) / (b.x - a.x);
    Solution s(2);
    s[0] = -a.x * c + a.y;
    s[1] = c;

    return s;
}

double lagrange(const std::vector<Point>& points, double x) {
    Matrix g(points.size()); //G matrix

    for (uint i = 0; i < g.size(); i++) {
        g[i] = Row(points.size());

        for (uint j = 0; j < points.size(); j++) {
            if (i == j) {
                g[i][j] = x - points[j].x; //Main diagonal
            } else {
                g[i][j] = points[i].x - points[j].x;
            }
        }
    }

    printMatrix(g);

    double sum = 0;
    double multiplier = 1;
    for (uint i = 0; i < points.size(); i++) {
        multiplier *= g[i][i]; //Gd

        double denominator = 1; //Product of this row
        for (uint j = 0; j < points.size(); j++) {
            denominator *= g[i][j];
        }

        sum += points[i].y / denominator;
    }

    return sum * multiplier;
}

Matrix computeDividedDifferencesTable(const std::vector<Point>& points) {
    Matrix m(points.size(), Row(points.size() + 1));

    for (uint i = 0; i < points.size(); i++) {
        m[i][0] = points[i].x;
        m[i][1] = points[i].y;
    }

    for (uint j = 2; j < m.front().size(); j++) {
        uint order = j - 1;

        for (uint i = 0; i < m.size() - order; i++) {
            //Main divided differences division
            m[i][j] = (m[i + 1][j - 1] - m[i][j - 1]) / (m[i + order][0] - m[i][0]);
        }
    }

    printMatrix(m);
    return m;
}


Solution newtonPolynomial(const std::vector<Point>& points) {
    Matrix m = computeDividedDifferencesTable(points);

    Solution solution(points.size());
    solution[0] = points[0].y;

    for (uint i = 1; i < solution.size(); i++) {
        //Representação do produtório da forma de Newton como um vetor de coeficientes negativos
        std::vector<double> coefs;
        for (uint j = 0; j < i; j++) {
            coefs.push_back(-points[j].x);
        }

        //Multiplicação entre o produtório e o resultado das diferenças divididas para este índice
        Solution partial = constructSimplePolynomial(coefs) * m[0][i + 1];

        for (uint j = 0; j < partial.size(); j++) {
            solution[j] += partial[j];
        }
    }

    return solution;
}
