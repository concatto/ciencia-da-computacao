#include "stack.h"
#include <iostream>

double operar(Stack<double> numeros, Stack<char> operacoes) {
	while (numeros.getSize() > 1) {
		double a = numeros.pop();
		double b = numeros.pop();
		
		char op = operacoes.pop();
		if (op == '+') {
			numeros.push(a + b);
		} else if (op == '-') {
			numeros.push(a - b);
		} else if (op == '*') {
			numeros.push(a * b);
		} else if (op == '/') {
			numeros.push(a / b);
		}
	}
	
	return numeros.pop();
}

int main() {
	Stack<double> numeros({5, 10, 15, 10});
	Stack<char> ops({'+', '+', '+'});
	
	std::cout << operar(numeros, ops);
}