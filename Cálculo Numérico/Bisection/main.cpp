#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <utility>
#include <functional>
#include <tuple>
#include <vector>

enum Method {Bisection, FalsePosition, Newton, Secant};
using Function = std::function<double(double)>;
using Problem = std::tuple<Function, double, double>;
using DerivativeProblem = std::tuple<Function, Function, double>;

const double Precision = 0.0000000001;

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

double bisection(std::ostream& out, Function func, double a, double b, bool falsePosition = false) {
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

        out << k << "," << a << "," << b << "," << x << "," << y << ",";
        if (k == 0) {
            out << "-";
        } else {
            out << epsilon;
        }
        out << "\n";

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

double falsePosition(std::ostream& out, Function func, double a, double b) {
    return bisection(out, func, a, b, true);
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

        out << k << "," << x << "," << y << "," << yDerivative << ",";
        if (k == 0) {
            out << "-";
        } else {
            out << epsilon;
        }
        out << "\n";

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

        out << k << "," << x << "," << y << "," << yDerivative << ",";
        if (k == 1) {
            out << "-";
        } else {
            out << epsilon;
        }
        out << "\n";

        prevX = x;
        x = x - (y / yDerivative);
        k++;
    } while (epsilon > Precision && y != 0);

    return x;
}

template <class T>
void solve(std::vector<T>& problems, const std::string& folder, std::function<void(std::ostream&,T&)> solver) {
    for (unsigned int i = 0; i < problems.size(); i++) {
        std::ostringstream ss;
        ss << folder << "/" << (i + 1) << ".csv";
        std::ofstream file(ss.str(), std::ios_base::trunc);

        solver(file, problems[i]);

        std::cout << "Solved " << ss.str() << "\n";
    }
}

int main()
{
    std::vector<Function> functions {
        //Bisection
        [](double x) { return std::pow(x, 3) + 3 * x - 1; },
        [](double x) { return std::pow(x, 2) - std::sin(x); },
        [](double x) { return 4 * x - std::exp(x); },
        //False Position
        [](double x) { return x - 2 * std::sin(x); },
        [](double x) { return std::cos(x) - std::exp(x); },
        [](double x) { return std::sin(x) - x * std::exp(x); },
        //Newton
        [](double x) { return 5 * std::pow(x, 3) + std::pow(x, 2) - 12 * x + 4; },
        [](double x) { return 2 * x - std::tan(x); },
        [](double x) { return std::sin(x) - std::exp(x); },
        //Secant
        [](double x) { return x - 3 * std::log(x); },
        [](double x) { return std::log(x) - std::cos(x); },
        [](double x) { return std::exp(-x) - std::log(x); },
        //Derivatives
        [](double x) { return 15 * std::pow(x, 2) + 2 * x - 12; },
        [](double x) { return 2 - std::pow(1.0 / std::cos(x), 2); },
        [](double x) { return std::cos(x) - std::exp(x); },
    };

    std::vector<Problem> problems1 {
        Problem(functions[0], 0, 1),
        Problem(functions[1], -0.2, 0.2),
        Problem(functions[1], 0.8, 1),
        Problem(functions[2], 0, 1),
        Problem(functions[2], 2, 3)
    };

    std::vector<Problem> problems2 {
        Problem(functions[3], -3, -1),
        Problem(functions[3], -0.5, 0.5),
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
        Problem(functions[9], 1, 1.5),
        Problem(functions[9], 3.5, 4),
        Problem(functions[10], 0.5, 1),
        Problem(functions[11], 0.5, 1)
    };


    /*solve<Problem>(problems1, "1", [](std::ostream& out, Problem& problem) {
        bisection(out, std::get<0>(problem), std::get<1>(problem), std::get<2>(problem));
    });

    solve<Problem>(problems2, "2", [](std::ostream& out, Problem& problem) {
        falsePosition(out, std::get<0>(problem), std::get<1>(problem), std::get<2>(problem));
    });

    solve<DerivativeProblem>(problems3, "3", [](std::ostream& out, DerivativeProblem& problem) {
        newton(out, std::get<0>(problem), std::get<1>(problem), std::get<2>(problem));
    });

    solve<Problem>(problems4, "4", [](std::ostream& out, Problem& problem) {
        secant(out, std::get<0>(problem), std::get<1>(problem), std::get<2>(problem));
    });*/

    //secant(std::cout, [](double x) { return 3 * x * x + 10 * x; }, -3, -2);
    //falsePosition(std::cout, [](double x) { return x * x - std::sin(x); }, 0.5, 1.5);
    bisection(std::cout, functions[1], 0.6, 1.2);
}

