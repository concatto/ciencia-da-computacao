#include "closed_hash_table.h"
#include "open_hash_table.h"
#include "Windows.h"
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(std::time(nullptr));
	OpenHashTable<int, int> table;

	for (int i = 0; i < 2000; i++) {
		std::cout << "t resu: " << table.insert(1 + (std::rand() % 31999), i) << "; it " << table.getIterations() << " i = " << i << "\n";
		Sleep(10);
	}
}
