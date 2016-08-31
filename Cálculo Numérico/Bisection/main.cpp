#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <utility>
#include <functional>
#include <tuple>
#include <vector>
#include <iomanip>

using Function = std::function<double(double)>;
using Problem = std::tuple<Function, double, double>;
using DerivativeProblem = std::tuple<Function, Function, double>;

const double Precision = 0.0000000001;

std::string toString(double value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

namespace RootFinder {
    double approximateDerivative(Function function, double x, double prevX) {
        return (function(x) - function(prevX)) / (x - prevX);
    }

    double error(double x, double prevX) {
        if (x != 0) {
            return std::abs((x - prevX) / x);
        }

        return 1;
        std::cout << "Division by zero!\n";
    }

    double intervalSearch(std::ostream& out, Function func, double a, double b, bool falsePosition) {
        unsigned int k = 0;
        double x;
        double y;
        double epsilon;
        double prevX = 0;
        out << "k,a,b,xk,f(xk),epsilon\n";
        do {
            if (falsePosition) {
                x = (a * func(b) - b * func(a)) / (func(b) - func(a));
            } else {
                x = (a + b) / 2.0;
            }

            y = func(x);
            epsilon = error(x, prevX);

            if (epsilon < 0.0001) out << std::setprecision(12);
            out << k << "," << a << "," << b << "," << x << "," << y << "," << (k == 0 ? "-" : toString(epsilon)) << "\n";

            if (func(a) * y < 0) {
                b = x;
            } else {
                a = x;
            }

            prevX = x;
            k++;
        } while (epsilon > Precision && y != 0);

        return x;
    }

    double bisection(std::ostream& out, Function func, double a, double b) {
        return intervalSearch(out, func, a, b, false);
    }

    double falsePosition(std::ostream& out, Function func, double a, double b) {
        return intervalSearch(out, func, a, b, true);
    }

    double newton(std::ostream& out, Function func, Function derivative, double x) {
        unsigned int k = 0;
        double y;
        double yDerivative;
        double epsilon;
        double prevX = 0;
        out << "k,xk,f(xk),fd(xk),epsilon\n";
        do {
            y = func(x);
            yDerivative = derivative(x);
            epsilon = error(x, prevX);

            if (epsilon < 0.0001) out << std::setprecision(12);
            out << k << "," << x << "," << y << "," << yDerivative << "," << (k == 0 ? "-" : toString(epsilon)) << "\n";

            prevX = x;
            x = x - (y / yDerivative);
            k++;
        } while (epsilon > Precision && y != 0);

        return x;
    }

    double secant(std::ostream& out, Function func, double x, double prevX) {
        unsigned int k = 1;
        double y;
        double yDerivative;
        double epsilon;
        out << "k,xk,f(xk),fd(xk),epsilon\n";
        out << "0," << prevX << "," << func(prevX) << ",-,-\n";
        do {
            y = func(x);
            yDerivative = approximateDerivative(func, x, prevX);
            epsilon = error(x, prevX);

            if (epsilon < 0.0001) out << std::setprecision(12);
            out << k << "," << x << "," << y << "," << yDerivative << "," << (k == 1 ? "-" : toString(epsilon)) << "\n";

            prevX = x;
            x = x - (y / yDerivative);
            k++;
        } while (epsilon > Precision && y != 0);

        return x;
    }
}

template <class T, class Func>
void solve(std::vector<T>& problems, const std::string& folder, Func solver) {
    for (unsigned int i = 0; i < problems.size(); i++) {
        std::ostringstream ss;
        ss << folder << "/" << (i + 1) << ".csv";
        std::ofstream file(ss.str(), std::ios_base::trunc);

        std::cout << "Starting... ";

        solver(file, std::get<0>(problems[i]), std::get<1>(problems[i]), std::get<2>(problems[i]));

        std::cout << "Solved " << ss.str() << "\n";
    }
}

int main()
{
    std::vector<Function> functions {
        //Bisection (0-2)
        [](double x) { return std::pow(x, 3) + 3 * x - 1; },
        [](double x) { return std::pow(x, 2) - std::sin(x); },
        [](double x) { return 4 * x - std::exp(x); },
        //False Position (3-5)
        [](double x) { return x - 2 * std::sin(x); },
        [](double x) { return std::cos(x) - std::exp(x); },
        [](double x) { return std::sin(x) - x * std::exp(x); },
        //Newton (6-8)
        [](double x) { return 5 * std::pow(x, 3) + std::pow(x, 2) - 12 * x + 4; },
        [](double x) { return 2 * x - std::tan(x); },
        [](double x) { return std::sin(x) - std::exp(x); },
        //Secant (9-11)
        [](double x) { return x - 3 * std::log(x); },
        [](double x) { return std::log(x) - std::cos(x); },
        [](double x) { return std::exp(-x) - std::log(x); },
        //Derivatives (12-14)
        [](double x) { return 15 * std::pow(x, 2) + 2 * x - 12; },
        [](double x) { return 2 - std::pow(1.0 / std::cos(x), 2); },
        [](double x) { return std::cos(x) - std::exp(x); },
    };

    std::vector<Problem> problems1 {
        Problem(functions[0], -1, 1),
        //Problem(functions[1], -0.2, 0.5),
        Problem(functions[1], 0.8, 1),
        Problem(functions[2], 0, 1),
        Problem(functions[2], 2, 3)
    };

    std::vector<Problem> problems2 {
        Problem(functions[3], -3, -1),
        //Problem(functions[3], -0.5, 0.5),
        Problem(functions[3], 1, 3),
        Problem(functions[4], -2, -0.5),
        Problem(functions[4], -6, -4),
        Problem(functions[5], -4, -2),
        Problem(functions[5], -7, -6)
    };

    std::vector<DerivativeProblem> problems3 {
        DerivativeProblem(functions[6], functions[12], -2),
        DerivativeProblem(functions[6], functions[12], 0.5),
        DerivativeProblem(functions[6], functions[12], 1.5),
        DerivativeProblem(functions[7], functions[13], 1),
        DerivativeProblem(functions[7], functions[13], 4.7),
        DerivativeProblem(functions[8], functions[14], -6),
        DerivativeProblem(functions[8], functions[14], -3)
    };

    std::vector<Problem> problems4 {
        Problem(functions[9], 1.5, 1),
        Problem(functions[9], 4, 3.5),
        Problem(functions[10], 1, 0.5),
        Problem(functions[11], 1, 0.5)
    };

    solve(problems1, "Bisection", RootFinder::bisection);
    solve(problems2, "False Position", RootFinder::falsePosition);
    solve(problems3, "Newton", RootFinder::newton);
    solve(problems4, "Secant", RootFinder::secant);

    //secant(std::cout, [](double x) { return 3 * x * x + 10 * x; }, -3, -2);
    //falsePosition(std::cout, [](double x) { return x * x - std::sin(x); }, 0.5, 1.5);
    //bisection(std::cout, functions[1], 0.6, 1.2);
}
