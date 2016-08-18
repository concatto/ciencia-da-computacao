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

double derivative(Function function, double x, double prevX) {
    return (function(x) - function(prevX)) / (x - prevX);
}

double fd(double x) {
    return 0;
}

double f(double x) {
    return 4 * std::cos(x) - std::exp(2 * x);
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

double newton() {
    return 0;
}

double secant() {
    return 0;
}

template <class T>
void solve(const std::vector<T>& problems, const std::string& folder, Method m) {
    for (unsigned int i = 0; i < problems.size(); i++) {
        std::ostringstream ss;
        ss << folder << "/" << (i + 1) << ".csv";
        std::ofstream file(ss.str(), std::ios_base::trunc);

        const T& problem = problems[i];

        switch (m) {
        case Bisection:
        case FalsePosition:
            bisection(file, std::get<0>(problem), std::get<1>(problem), std::get<2>(problem), m == Method::FalsePosition);
            break;
        case Newton:
            newton();
            break;
        case Secant:
            secant();
            break;
        }

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
        [](double x) { return x - std::log(x); },
        [](double x) { return std::log(x) - std::cos(x); },
        [](double x) { return std::exp(-x) - std::log(x); },
        //Derivatives
        [](double x) { return 15 * std::pow(x, 2) + 2 * x - 12; },
        [](double x) { return 0; /* TODO */ },
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

    solve(problems1, "1", Method::Bisection);
    solve(problems2, "2", Method::FalsePosition);
}

