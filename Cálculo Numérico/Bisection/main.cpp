#include <iostream>
#include <functional>
#include <utility>
#include <cmath>

enum Method {Bisection, FalsePosition};

double f(double x) {
    return 4 * std::cos(x) - std::exp(2 * x);
    //return (x / 2.0) - std::tan(x);
}

double findRoot(double a, double b, double precision, Method m) {
    double x;
    double y;
    double epsilon;
    double prevX = 0;
    do {
        if (m == Method::Bisection) {
            x = (a + b) / 2.0;
        } else if (m == Method::FalsePosition) {
            x = (a * f(b) - b * f(a)) / (f(b) - f(a));
        }

        y = f(x);

        if (f(a) * y < 0) {
            b = x;
        } else {
            a = x;
        }

        if (x != 0) {
            epsilon = std::abs((x - prevX) / x);
        } else {
            epsilon = 1;
            std::cout << "Division by zero!\n";
        }
        prevX = x;

        std::cout << "a = " << a << "\n";
        std::cout << "b = " << b << "\n";
        std::cout << "x = " << x << "\n";
        std::cout << "f(x) = " << y << "\n";
        std::cout << "epsilon = " << epsilon << "\n";
        std::cout << "\n";
    } while (epsilon > precision);

    return x;
}

template <class T>
T machineEpsilon() {
    T a = 1;
    T b = 1;
    while (a + b != a) {
        b = b / 10;
        std::cout << b << "\n";
    }
    return b;
}

int main()
{
    /*machineEpsilon<float>();
    std::cout << "======\n";
    machineEpsilon<double>();*/

    double a;
    double b;
    bool root = false;

    std::cout << "Input A and B values:\n";

    do {
        std::cout << "a = ";
        std::cin >> a;
        double ya = f(a);
        std::cout << "f(a) = " << ya << "\n";

        std::cout << "b = ";
        std::cin >> b;
        double yb = f(b);
        std::cout << "f(b) = " << yb << "\n";

        if (ya * yb < 0) {
            root = true;
        } else {
            std::cout << "Try again.\n";
        }
    } while (!root);

    std::cout << "\nStarting the bisection algorithm with a = " << a << " and b = " << b << "...\n\n";
    findRoot(a, b, std::pow(10, -10), Method::Bisection);

    return 0;

}

