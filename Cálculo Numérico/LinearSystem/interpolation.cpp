#include "interpolation.h"

#include <cmath>
#include <sstream>
#include <algorithm>

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


std::vector<Point> reshapePoints(const std::vector<Point> &points) {
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
