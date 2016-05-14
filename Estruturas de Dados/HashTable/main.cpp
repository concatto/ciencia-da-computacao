#include "closed_hash_table.h"
#include "open_hash_table.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

struct Result {
	double insertion;
	double search;
	Result() : insertion(0), search(0) {}
};

int generateRandom() {
	return (std::rand() % 31999) + 1;
}

std::vector<Result> testTable(HashTable<int, int>& table, const std::vector<int>& startingSizes, int elements) {
	std::vector<Result> results;
	for (const int& size : startingSizes) {
		int fillAmount = size - table.getSize();
		for (int i = 0; i < fillAmount; i++) {
			table.insert(generateRandom(), 1); //Fill the table with random elements until it has the requested size
		}

		Result r;
		std::cout << "Table has " << table.getSize() << " elements.\n";
		for (int i = 0; i < elements; ) {
			//if (table.getSize() < 1000) {
				bool success = table.insert(generateRandom(), 1);
				//std::cout << "Tried to insert. Took " << table.getIterations() << " iterations.\n";
				r.insertion += static_cast<double>(table.getIterations()) / elements;

				while (!success) { //If the insertion didn't succeed, keep trying until an element is inserted
					success = table.insert(generateRandom(), 1);
				}
			//}

			table.find(generateRandom());
			r.search += static_cast<double>(table.getIterations()) / elements;

			i++;
		}

		results.push_back(r);
	}

	return results;
}

void runTests(HashTable<int, int>& table, int tests, const std::vector<int>& startingSizes) {
	std::vector<Result> averages(startingSizes.size());

	for (int i = 0; i < tests; i++) {
		table.clear();
		std::vector<Result> results = testTable(table, startingSizes, 10);

		std::cout << "Test " << i << ":\n";
		for (int j = 0; j < results.size(); j++) {
			averages[j].insertion += results[j].insertion / tests;
			averages[j].search += results[j].search / tests;
			std::cout << "Insertion: " << results[j].insertion << "; Search: " << results[j].search << "\n";
		}
		std::cout << "\n\n";
	}

	std::cout << "Tests completed.\n";
	//std::ofstream arquivo("closed.csv");
	for (int i = 0; i < averages.size(); i++) {
		std::cout << startingSizes[i] << ";" << averages[i].insertion << ";" << averages[i].search << "\n";
		//arquivo << startingSizes[i] << ";" << averages[i].insertion << ";" << averages[i].search << "\n";
	}
	//arquivo.close();
}

int main() {
	std::srand(std::time(nullptr));
	std::vector<int> sizes({90, 240, 490, 740, 990, 1990});

	ClosedHashTable<int, int> table;
	runTests(table, 100000, sizes);

}
