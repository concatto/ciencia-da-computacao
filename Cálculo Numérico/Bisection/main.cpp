#include <iostream>
#include <functional>
#include <utility>
#include <algorithm>

int main()
{
    std::function<double(double)> f = [](double x) { return x * x + 2 * x - 9; };

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

        std::cout << "a = " << ya << "\nb = " << yb << "\n";

        if (ya * yb < 0) {
            root = true;
        } else {
            std::cout << "Try again.\n";
        }
    } while (!root);

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

        std::cout << "f(x) = " << y << " eps " << epsilon << "\n";
    } while (epsilon > 0.0001);
}

