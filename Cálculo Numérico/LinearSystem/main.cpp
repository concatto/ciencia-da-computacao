#include "linearsystem.h"
#include "interpolation.h"
#include <fstream>

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

    Matrix m6 = {
        {10, 2, 1, 7},
        {1, 5, 1, -8},
        {2, 3, 10, 6}
    };

    Matrix m7 = {
        {10, 3, -2, 57},
        {2, 8, -1, 20},
        {1, 1, 5, -4}
    };

    Matrix m8 = {
        {4, -1, 0, -1, 0, 0, 0, 0, 0, 0, -110},
        {-1, 4, -1, 0, -1, 0, 0, 0, 0, 0, -30},
        {0, -1, 4, 0, 0, -1, 0, 0, 0, 0, -40},
        {-1, 0, 0, 4, -1, 0, 0, 0, 0, 0, -110},
        {0, -1, 0, -1, 4, -1, -1, 0, 0, 0, 0},
        {0, 0, -1, 0, -1, 4, 0, -1, 0, 0, -15},
        {0, 0, 0, 0, -1, 0, 4, -1, 0, 0, -90},
        {0, 0, 0, 0, 0, -1, -1, 4, -1, 0, -25},
        {0, 0, 0, 0, 0, 0, 0, -1, 4, -1, -55},
        {0, 0, 0, 0, 0, 0, 0, 0, -1, 4, -65}
    };

    Matrix m9 = {
        {4, -1, 3, 8, 43},
        {1, 6, 2, -3, 7},
        {5, 5, 1, 0, 18},
        {2, 4, -2, 1, 8}
    };

    Matrix m10 = {
        {3, -2, 5, 1, 7},
        {-6, 4, -8, 1, -9},
        {4, -6, 19, 1, 23},
        {6, -4, -6, 15, 11}
    };

    Matrix m11 = {
        {0.252, 0.36, 0.12, 7},
        {0.112, 0.16, 0.24, 8},
        {0.147, 0.21, 0.25, 9}
    };

    Matrix m12 = {
        {10, 1, 1, 12},
        {1, 10, 1, 12},
        {1, 1, 10, 12}
    };

    Matrix m13 = {
        {4, -1, 0, 0, 1},
        {-1, 4, -1, 0, 1},
        {0, -1, 4, -1, 1},
        {0, 0, -1, 4, 1}
    };

    /*
    Solution s = polynomialInterpolation({{1, 1}, {2, 9}, {3, 28}}, [&](const Matrix& matrix) {
        return solveSystem(matrix, true);
    });

    std::cout << toFunctionString({9, 2, 0, 4}) << "\n";*/

    //std::cout << toFunctionString(linearInterpolation(Point(0.74, 0.98), Point(0.99, 0.001))) << "\n";

    //std::cout << lagrange({{0.1, 1.221}, {0.6, 3.320}, {0.8, 4.953}}, 0.2) << "\n";
    std::vector<Point> data{
        {183, 79}, {173, 69}, {168, 70}, {188, 81},
        {158, 61}, {163, 63}, {178, 73}
    };

    sortPoints(data);
    //std::cout << lagrange(data2, 82) << "\n";


    std::vector<Point> data2 = reshapePoints(data);

    sortPoints(data2);
    //std::cout << lagrange(data2, 82) << "\n";

    //std::ofstream file("abcde.txt");
    Solution s = polynomialInterpolation(data, [&](const Matrix& matrix) {
        printMatrix(matrix);

        Matrix m = gaussianElimination(matrix, true);
        printMatrix(m);
        return solveSystem(matrix, false);
    });

    printRow(s);
    //std::ofstream file("abc.txt");
    //file << "\n" << toFunctionString(s) << "\n";
}

