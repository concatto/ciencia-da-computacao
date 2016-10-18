#include "utils.h"
#include <cmath>
#include <sstream>
#include <algorithm>

void printRow(const Row& row, std::ostream& out) {
    for (double d : row) {
        out << d << " ";
    }
    out << "\n";
}

void printMatrix(const Matrix& m, std::ostream& out) {
    for (const Row& row : m) {
        printRow(row, out);
    }
}

bool nearZero(double value) {
    double limit = 1E-11;
    return value < limit && value > (0 - limit);
}

std::string toFunctionString(Solution solution) {
    std::ostringstream oss;
    oss << std::fixed;

    uint highestExponent = solution.size() - 1;
    uint exponent = highestExponent;
    for (Solution::reverse_iterator it = solution.rbegin(); it != solution.rend(); ++it) {
        double value = *it;

        if (value != 0) {
            if (value < 0) {
                oss << "-";
                if (exponent < highestExponent) {
                    oss << " ";
                }
            } else if (exponent < highestExponent) {
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

/*
 * Constructs a vector from the product of the given set of coefficients.
 * For example, the set {2, 3} representing (x + 2)(x + 3) would be transformed
 * into [6, 5, 1] representing x^2 + 5x + 6.
 *
 */
Solution constructSimplePolynomial(const std::vector<double>& coefficients) {
    Solution result(coefficients.size() + 1, 0);
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

//Transforms (x, y) into (y, x).
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

std::vector<std::vector<uint>> permutations(uint quantity) {
    std::vector<std::vector<uint>> container;
    std::vector<uint> remaining;

    for (uint i = 0; i < quantity; i++) {
        remaining.push_back(i);
    }

    do {
        container.push_back(remaining);
    } while (std::next_permutation(remaining.begin(), remaining.end()));

    return container;
}

Row operator*(const Matrix& matrix, const Row& row) {
    Row result(row.size(), 0);

    for (uint i = 0; i < matrix.front().size() - 1; i++) {
        for (uint j = 0; j < row.size(); j++) {
            result[j] += row[j] * matrix[i][j];
        }
    }

    return result;
}
