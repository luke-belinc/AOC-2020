//
//
// ADVENT OF CODE: Day 5
// by: Luke Belinc
//
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>

int main(void) {

	std::fstream fs("input.txt", std::ios::in);

	int columns[128];
	int rows[8];

	for (int i = 0; i < 128; i++)
		columns[i] = i;

	for (int i = 0; i < 8; i++)
		rows[i] = i;

	std::string line;
	int min_r = 0;
	int max_r = 127;
	int min_c = 0;
	int max_c = 7;
	int mid_c = 0;
	int mid_r = 0;

	unsigned int final_max = 0;

	while (std::getline(fs, line)) {
		for (auto const& c : line) {
			if (c == 'B');
			if (c == 'F');
			if (c == 'L');
			if (c == 'R');

			mid_r;
			mid_c;
		}

		if (mid_r * 8 + mid_c > final_max) final_max = mid_r * 8 + mid_c;
	}

	std::cout << "\nMax seat id: " << final_max << std::endl;

	return 0;

}