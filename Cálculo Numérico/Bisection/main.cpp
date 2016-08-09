#include <iostream>
#include <functional>
#include <utility>
#include <cmath>

double f(double x) {
    return std::pow(x + 1, 2) * std::exp(x * x - 2) - 1;
}

int main()
{
    double a;
    double b;
    double x;
    double y;

    bool root = false;

    do {
        std::cin >> a;
        std::cin >> b;

        double ya = f(a);
        double yb = f(b);

        std::cout << "f(a) = " << ya << "\n";
        std::cout << "f(b) = " << yb << "\n";

        if (ya * yb < 0) {
            root = true;
        } else {
            std::cout << "Try again.\n";
        }
    } while (!root);

    std::cout << "\nStarting the bisection algorithm...\n\n";

    double epsilon;
    double prevX = 0;
    do {
        x = (a + b) / 2.0;

        y = f(x);

        if (f(a) * y < 0) {
            b = x;
        } else {
            a = x;
        }

        epsilon = std::abs((x - prevX) / x);
        prevX = x;

        std::cout << "a = " << a << "\n";
        std::cout << "b = " << b << "\n";
        std::cout << "x = " << x << "\n";
        std::cout << "f(x) = " << y << "\n";
        std::cout << "epsilon = " << epsilon << "\n";
        std::cout << "\n";
    } while (epsilon > 0.0001);
}

