#include <iostream>
#include <functional>
#include <utility>
#include <cmath>

enum Method {Bisection, FalsePosition, Newton, Cosecant};

double fd(double x) {
    return 0;
}

double f(double x) {
    return 4 * std::cos(x) - std::exp(2 * x);
}

double bisection(double a, double b, double precision, bool falsePosition) {
    unsigned int k = 1;
    double x;
    double y;
    double epsilon;
    double prevX = 0;
    do {
        if (falsePosition) {
            x = (a * f(b) - b * f(a)) / (f(b) - f(a));
        } else {
            x = (a + b) / 2.0;
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

        std::cout << "k = " << k << "\n";
        std::cout << "a = " << a << "\n";
        std::cout << "b = " << b << "\n";
        std::cout << "x = " << x << "\n";
        std::cout << "f(x) = " << y << "\n";
        std::cout << "epsilon = " << epsilon << "\n";
        std::cout << "\n";
        k++;
    } while (epsilon > precision);

    return x;
}

double newton() {
    return 0;
}

double cosecant() {
    return 0;
}

double findRoot(double a, double b, double precision, Method m) {
    switch (m) {
        case Bisection:
        case FalsePosition:
            return bisection(a, b, precision, m == Method::FalsePosition);
        case Newton:
            return newton();
        case Cosecant:
            return cosecant();
    }

    return 0;
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

    std::cout << "\nStarting the algorithm with a = " << a << " and b = " << b << "...\n\n";
    findRoot(a, b, std::pow(10, -10), Method::Bisection);

    return 0;

}

