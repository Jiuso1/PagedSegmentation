#include <iostream>
#include <vector>
#include <string>
#include "segmentEntry.h"
#include "pageEntry.h"

#define MEMSIZE 32

//Function headers:
void showTables(const std::vector<SegmentEntry>& segmentTable, const std::vector<std::vector<PageEntry>>& pageTables);
void showMainMemory(std::vector<std::string>& mainMemory);
void generateMainMemory(std::vector<std::string>& mainMemory, const int& stbr, const std::vector<SegmentEntry>& segmentTable, const std::vector<std::vector<PageEntry>>& pageTables);

int main() {
	std::vector<SegmentEntry> segmentTable = {
		{0, 2},
		{5, 8}
	};
	std::vector<std::vector<PageEntry>> pageTables = {};
	int stbr = 17;//Saves first segment table frame.
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
	generateMainMemory(mainMemory, stbr, segmentTable, pageTables);
	showMainMemory(mainMemory);

	return 0;
}

//Function implementations:
void showTables(const std::vector<SegmentEntry>& segmentTable, const std::vector<std::vector<PageEntry>>& pageTables) {
	size_t numberOfSegments = segmentTable.size();
	SegmentEntry segmentEntry = {};
	PageEntry pageEntry = {};
	size_t numberOfPages = 0;

	std::cout << "Segment table of process P" << std::endl;

	for (int i = 0; i < numberOfSegments; i++) {
		std::cout << "Basis\tLimit" << std::endl;
		segmentEntry = segmentTable[i];
		std::cout << segmentEntry.basis << "\t" << segmentEntry.limit << std::endl;
		std::cout << "\t\tFrame\tValidity bit" << std::endl;
		numberOfPages = pageTables[i].size();
		for (int j = 0; j < numberOfPages; j++) {
			pageEntry = pageTables[i][j];
			std::cout << "\t\t" << pageEntry.frame << "\t" << pageEntry.validityBit << "\t\t(Page " << j << " of segment " << i << ")" << std::endl;
		}
	}
}

void generateMainMemory(std::vector<std::string>& mainMemory, const int& stbr, const std::vector<SegmentEntry>& segmentTable, const std::vector<std::vector<PageEntry>>& pageTables) {
	size_t numberOfSegments = segmentTable.size();
	SegmentEntry segmentEntry = {};
	PageEntry pageEntry = {};
	std::string pageName = "";
	size_t numberOfPages = 0;

	//Fills the memory with empty values
	for (int i = 0; i < MEMSIZE; i++) {
		mainMemory.push_back("-");
	}

	//Fills the memory with ST locations
	for (int i = 0; i < numberOfSegments; i++) {
		mainMemory[stbr + i] = "ST";
	}

	//Fills the memory with PT locations
	//Remember that the number of page tables is equal to the number of segments
	for (int i = 0; i < numberOfSegments; i++) {
		segmentEntry = segmentTable[i];
		for (int j = segmentEntry.basis; j <= segmentEntry.limit + segmentEntry.basis; j++) {
			mainMemory[j] = "PT" + std::to_string(i);
		}
	}

	//Fills the memory with pages
	for (int i = 0; i < numberOfSegments; i++) {
		numberOfPages = pageTables[i].size();
		for (int j = 0; j < numberOfPages; j++) {
			pageName = "S" + std::to_string(i) + "P" + std::to_string(j);
			mainMemory[pageTables[i][j].frame] = pageName;
		}
	}
}

void showMainMemory(std::vector<std::string>& mainMemory) {
	std::cout << "Main Memory" << std::endl;
	std::cout << "Frame\tContent" << std::endl;

	for (int i = 0; i < MEMSIZE; i++) {
		std::cout << i << "\t" << mainMemory[i] << std::endl;
	}
}