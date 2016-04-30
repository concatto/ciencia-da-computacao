#include "closed_hash_table.h"
#include "open_hash_table.h"
#include "Windows.h"
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(std::time(nullptr));
	OpenHashTable<int, int> table;

	for (int i = 0; i < 900; i++) {
		table.insert(1 + (std::rand() % 1000), i);
	}
	
	for (int i = 0; i < 2000; i++) {
		std::cout << "found: " << table.find(1 + (std::rand() % 5000)) << "; it " << table.getIterations() << " i = " << i << " size: " << table.getSize() << "\n";
		Sleep(100);
	}
}
