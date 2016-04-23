#include "closed_hash_table.h"

int main() {
	ClosedHashTable<int, int> table;
	table.insert(1, 100);
	std::cout << table.find(1) << "\n";
}
