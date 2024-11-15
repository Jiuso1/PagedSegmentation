#include <iostream>
#include <vector>
#include "segmentEntry.h"
#include "pageEntry.h"

void showTables(const std::vector<SegmentEntry>& segmentTable, const std::vector<std::vector<PageEntry>>& pageTables);
void showMemory(const std::vector<std::string>& mainMemory);
void generateMemory(const std::vector<std::string>& mainMemory);

int main() {
	std::vector<SegmentEntry> segmentTable = {
		{0, 2},
		{5, 8}
	};
	std::vector<std::vector<PageEntry>> pageTables = {};
	int stbr = 0;//Saves first segment table frame.
	std::vector<std::string> mainMemory = {};

	pageTables.push_back({
		{15, 1},
		{16, 1}
		});

	pageTables.push_back({
		{20, 1},
		{21, 1},
		{22, 1}
		});

	showTables(segmentTable, pageTables);

	return 0;
}

void showTables(const std::vector<SegmentEntry>& segmentTable, const std::vector<std::vector<PageEntry>>& pageTables) {
	size_t numberOfSegments = 0;
	SegmentEntry segmentEntry = {};
	PageEntry pageEntry = {};

	std::cout << "Segment table of process P" << std::endl;
	numberOfSegments = segmentTable.size();

	for (int i = 0; i < numberOfSegments; i++) {
		std::cout << "Basis\tLimit" << std::endl;
		segmentEntry = segmentTable[i];
		std::cout << segmentEntry.basis << "\t" << segmentEntry.limit << std::endl;
		std::cout << "\t\tFrame\tValidity bit" << std::endl;
		for (int j = 0; j < pageTables[i].size(); j++) {
			pageEntry = pageTables[i][j];
			std::cout << "\t\t" << pageEntry.frame << "\t" << pageEntry.validityBit << "\t\t(Page " << j << " of segment " << i << ")" << std::endl;
		}
	}
}

void showMemory(const std::vector<std::string>& mainMemory) {
	std::cout << "Main Memory" << std::endl;
	std::cout << "Frame\tContent" << std::endl;

	for(int i = 0; i < main
}

void generateMemory(const std::vector<std::string>& mainMemory) {

}