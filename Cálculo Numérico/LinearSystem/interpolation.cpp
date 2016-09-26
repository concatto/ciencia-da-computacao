#include "interpolation.h"

#include <cmath>
#include <sstream>

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
