#include <iostream>
#include <unordered_map>

using uint = unsigned int;
using Memory = std::unordered_map<uint, uint>;

uint getPageTable(uint address) {
	return (address >> 22) & 0x3ff;
}

uint getPageNumber(uint address) {
	return (address >> 12) & 0x3ff;
}

uint getOffset(uint address) {
	return address & 0xfff;
}

uint decodeFrameAddress(uint data) {
	return data & 0xfffff000;
}

int main(int argc, char** argv) {
	Memory mem;
	
	mem[0x0001a038] = 0x000b4045;
	mem[0x000b4b9c] = 0x236b12c1;
	mem[0x000b91a0] = 0x1b9d8fc5;
	mem[0x001b31cc] = 0x003a9067;
	mem[0x001b3458] = 0x0001a067;
	mem[0x003a9054] = 0x000b9067;
	
	uint virtualAddress = 0x4580eb9c;
	uint directoryBase = 0x001b3000;
	
	//Directory contains page tables
	uint pageTableAddress = directoryBase + (getPageTable(virtualAddress) << 2);
	uint pageTableData = mem[pageTableAddress];
	std::cout << std::hex << pageTableAddress << " => " << pageTableData << "\n";
	
	//Page table contains pages
	uint pageAddress = decodeFrameAddress(pageTableData) + (getPageNumber(virtualAddress) << 2);
	uint pageData = mem[pageAddress];
	std::cout << std::hex << pageAddress << " => " << pageData << "\n";
	
	//Page contains data
	uint dataAddress = decodeFrameAddress(pageData) + (getOffset(virtualAddress));
	uint data = mem[dataAddress];
	
	std::cout << std::hex << dataAddress << " => " << data << "\n";
}