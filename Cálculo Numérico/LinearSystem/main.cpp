#include "definitions.h"
#include "linearsystem.h"
#include "interpolation.h"
#include "utils.h"
#include <fstream>

void problem1() {
    Matrix m = {
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

    Solution sol = solveSystem(m, true);
    printRow(sol);
    verifySolution(sol, m);
}

void problem2() {
    Matrix m = {
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

    testSassenfeldCriterion(m);
    Solution sol = solveSystemIteratively(m, 1E-10, IterativeMode::GaussSeidel);
    printRow(sol);
    verifySolution(sol, m);
}

void problem3() {

    Matrix a = {
        {2, 3, 1, 1, 7},
        {1, -1, 2, -1, 1},
        {3, 2, -3, -2, 4},
        {4, 3, 2, 1, 12},
    };

    Solution solA = solveSystem(a, true);
    printRow(solA);
    verifySolution(solA, a);


    Matrix b = {
        {3, -2, 5, 1, 7},
        {-6, 4, -8, 1, -9},
        {9, -6, 19, 1, 23},
        {6, -4, -6, 15, 11}
    };

    Solution solB = solveSystem(b, true);
    printRow(solB);
    verifySolution(solB, b);


    Matrix c = {
        {0.252, 0.36, 0.12, 7},
        {0.112, 0.16, 0.24, 8},
        {0.147, 0.12, 0.25, 9}
    };

    Solution solC = solveSystem(c, true);
    printRow(solC);
    verifySolution(solC, c);
}

void subproblem4(Matrix m) {
    std::vector<std::vector<uint>> p = permutations(m.size());
    for (const std::vector<uint>& k : p) {
        Matrix mod;
        for (uint i : k) {
            mod.push_back(m[i]);
        }

        if (testSassenfeldCriterion(mod)) {
            m = mod;
            break;
        }
    }

    printMatrix(m);

    Solution sol = solveSystemIteratively(m, 1E-10, IterativeMode::GaussSeidel);
    printRow(sol);
    verifySolution(sol, m);
}

void problem4() {
    Matrix a = {
        {10, 1, 1, 12},
        {1, 10, 1, 12},
        {1, 1, 10, 12}
    };

    subproblem4(a);

    Matrix b = {
        {4, -1, 0, 0, 1},
        {-1, 4, -1, 0, 1},
        {0, -1, 4, -1, 1},
        {0, 0, -1, 4, 1},
    };

    subproblem4(b);

    Matrix c = {
        {1, 1, -1, 2, -1, 2},
        {2, 0, 0, 0, 0, 2},
        {0, 2, 0, 0, 0, 2},
        {4, 0, 0, 16, 0, 20},
        {0, 0, 4, 0, 0, 4}
    };

    subproblem4(c);
}

void problem5() {
    std::vector<Point> points{
        {2, 7.38}, {2.2, 9.02}, {2.4, 11.02}, {2.6, 13.46}, {2.8, 16.44},
        {3, 20.08}, {3.2, 24.53}, {3.4, 29.96}, {3.6, 36.59}, {3.8, 44.7}
    };

    Solution sol = polynomialInterpolation(points, [&](const Matrix& m) { return solveSystem(m, true); });
    printRow(sol);
    std::cout << toFunctionString(sol) << "\n";
    std::cout << "e^5 = " << applyFunction(sol, 5) << "\n";
    verifySolution(sol, points);
}

void problem6() {
    std::vector<Point> points = {{0, -2.78}, {0.5, -2.241}, {1, -1.65}, {1.5, -0.594}, {2, 1.34}, {2.5, 4.564}};
    Solution sol = newtonPolynomial(points);
    printRow(sol);

    std::cout << toFunctionString(sol) << "\n";
    verifySolution(sol, points);
}

int main()
{
    problem1();
    //problem2();
    //problem3();
    //problem4();
    //problem5();
    //problem6();


    /*
    std::vector<Point> data{{183, 79}, {173, 69}, {168, 70}, {188, 81}, {158, 61}, {163, 63}, {178, 73}};
    sortPoints(data);

    std::vector<Point> data2 = reshapePoints(data);
    sortPoints(data2);

    Solution s = polynomialInterpolation(data, [&](const Matrix& matrix) {
        printMatrix(matrix);

        Matrix m = gaussianElimination(matrix, true);
        printMatrix(m);
        return solveSystem(matrix, false);
    });

    printRow(s);
    */
}

