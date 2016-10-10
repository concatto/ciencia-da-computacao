#include "interpolation.h"

#include <cmath>
#include <sstream>
#include <algorithm>
#include <iomanip>

Row operator*(const Row& row, double c) {
    Row r;
    for (double v : row) {
        r.push_back(v * c);
    }
    return r;
}

Solution polynomialInterpolation(std::vector<Point> points, std::function<Solution(const Matrix&)> solver) {
    Matrix matrix;

    for (uint i = 0; i < points.size(); i++) {
        Row row;

        for (uint j = 0; j < points.size(); j++) {
            row.push_back(std::pow(points[i].x, j));
        }

        row.push_back(points[i].y);

        matrix.push_back(row);
    }


    return solver(matrix);
}


std::string toFunctionString(Solution solution) {
    std::ostringstream oss;
    oss << std::fixed;

    uint exponent = solution.size() - 1;
    for (Solution::reverse_iterator it = solution.rbegin(); it != solution.rend(); ++it) {
        double value = *it;

        if (value != 0) {
            if (value < 0) {
                oss << "- ";
            } else if (exponent < solution.size() - 1) {
                oss << "+ ";
            }
            if (value != 1) oss << std::abs(value);
            if (exponent > 0) oss << "x";
            if (exponent > 1) {
                oss << "^" << exponent;
            }
            oss << " ";
        }

        exponent--;
    }

    return oss.str();
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

Matrix rotateMatrixLeft(const Matrix& original) {
    Matrix m(original.front().size());

    for (uint i = 0; i < m.size(); i++) {
        Row row(original.size());

        for (uint j = 0; j < row.size(); j++) {
            std::cout << j << ", " << i << ", " << original.size() << ", " << original[j].size() << "\n";
            row[j] = original[j][i];

        }

        m[i] = row;
    }

    return m;
}

Matrix dividedDifferences(const std::vector<Point>& points) {
    Matrix m(points.size(), Row(points.size() + 1));

    for (uint i = 0; i < points.size(); i++) {
        m[i][0] = points[i].x;
        m[i][1] = points[i].y;
    }

    for (uint j = 2; j < m.front().size(); j++) {
        uint order = j - 1;

        for (uint i = 0; i < m.size() - order; i++) {
            m[i][j] = (m[i + 1][j - 1] - m[i][j - 1]) / (m[i + order][0] - m[i][0]);
        }
    }

    printMatrix(m);
    return m;
}

Row constructSimplePolynomial(const std::vector<double>& coefficients) {
    Row result(coefficients.size() + 1, 0);
    result[0] = coefficients[0];
    result[1] = 1;

    for (uint i = 1; i < coefficients.size(); i++) {
        for (int j = i; j >= 0; j--) {
            result[j + 1] = result[j];
        }

        result[0] = 0;

        for (uint j = 0; j < i + 1; j++) {
            result[j] += result[j + 1] * coefficients[i];
        }
    }

    return result;
}

double applyFunction(const Solution& solution, double x) {
    double result = 0;
    for (uint i = 0; i < solution.size(); i++) {
        result += solution[i] * std::pow(x, i);
    }
    return result;
}

Solution newtonPolynomial(const std::vector<Point>& points) {
    Matrix m = dividedDifferences(points);
    printMatrix(m);

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

std::vector<Point> reshapePoints(const std::vector<Point>& points) {
    std::vector<Point> r;
    for (const Point& p : points) {
        r.push_back(Point(p.y, p.x));
    }

    return r;
}

void sortPoints(std::vector<Point>& points, Axis axis, bool crescent) {
    std::sort(points.begin(), points.end(), [&](const Point& a, const Point& b) {
        if (axis == Axis::X) {
            return crescent ? a.x < b.x : a.x > b.x;
        } else {
            return crescent ? a.y < b.y : a.y > b.y;
        }
    });
}
