#include <iostream>
#include <priority_queue>
#include <unordered_map>

int main() {
	using std::unordered_map<char, int> = OccurrenceMap;
	std::string s = "baba a boca";
	OccurrenceMap map;
	
	for (char c : s) {
		OccurrenceMap::iterator it = map.find(c);
		if (c != map.end()) {
			it->second++;
		} else {
			map[c] = 1;
		}
	}
}