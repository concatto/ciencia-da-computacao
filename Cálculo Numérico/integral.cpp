#include <cmath>
#include <iostream>
#include <utility>
#include <functional>

using uint = unsigned int;
using Function = std::function<double(double)>;

double integral(Function function, double a, double b, uint precision) {
	double h = (b - a) / (precision - 1);
	//std::cout << "h = " << h << "\n";
	
	double sum = function(a) + function(b);
	for (uint i = 1; i < precision - 1; i++) {
		double x = a + (h * i);
		double y = function(x);
		//std::cout << "x = " << x << " -> " << y << "\n";
		sum += 2 * y;
	}
	
	//std::cout << sum << "\n";
	
	return sum * h * 0.5;
}

double f(double x) {
	return std::exp(-(x*x));
}

double error(double x) {
	return (2 / std::sqrt(3.1415926535)) * integral(f, 0, x, 1000);
}

int main(int argc, char** argv) {
	std::cout << 0.5 * error(std::stof(argv[1]) / std::sqrt(2)) << "\n";
}