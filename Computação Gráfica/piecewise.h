#ifndef PIECEWISE_H
#define PIECEWISE_H

#include <vector>
#include "defs.h"
#include "utils.h"

struct PiecewiseLinearFunction {
    std::vector<IntPair> coordinates;

    PiecewiseLinearFunction(const std::vector<IntPair>& coordinates) : coordinates(coordinates) {

    }

    int apply(int input) {
        int iUpper = 0;
        for (int i = 0; i < coordinates.size(); i++) {
            if (input <= coordinates[i].first) {
                iUpper = i;
                break;
            }
        }

        IntPair lower = coordinates[iUpper - 1];
        IntPair upper = coordinates[iUpper];

        double x = normalize(input, lower.first, upper.first);

        double ret = lerp(x, lower.second, upper.second);

        // std::cout << "in: " << input << "; norm: " << x << ";\n";
        // std::cout << "x0: " << lower.first << "; x1: " << upper.first << ";\n";
        // std::cout << "y0: " << lower.second << "; y1: " << upper.second << ". Out = " << ret << "\n";
        return ret;
    }
};

#endif