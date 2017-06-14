#include <vector>
#include <iostream>

int main() {
	std::vector<int> vec;
	vec.insert(vec.end(), {1, 2, 3, 4, 11});

	double sum = 0;
	for (int v : vec) {
		sum += v;
	}

	std::cout << sum << "\n";
}
