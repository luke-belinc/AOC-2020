#include <iostream>
#include <string>
#include <fstream>

int main(void) {

	// file stream object
	std::fstream f;
	f.open("input.txt", std::ios::in);

	// counters for number of valid passwords for part 1 and 2
	int validPart1 = 0;
	int validPart2 = 0;

	// line placeholder
	std::string line;
	// loop over lines within input stream
	while (std::getline(f, line)) {

		// delimiter positions
		size_t pos1 = line.find(":");
		size_t pos2 = line.find("-");

		// required character
		char req = line.substr(pos1 - 1, pos1)[0];

		// limits/indeces
		int min = std::stoi(line.substr(0, pos2));
		int max = std::stoi(line.substr(pos2 + 1, pos1 - 2));

		// password substring
		std::string pass = line.substr(pos1 + 2);

		/* part 1 */

		// calculate number of occurances of req within string
		int count = 0;
		for (char c : pass)
			if (c == req)
				count += 1;
		// check bounds on occurances
		if (count >= min && count <= max)
			validPart1 += 1;

		/* part 2 */

		// check for single occurance of req in first index
		if (pass[min] == req) {
			if (max < pass.size())
				if (pass[max] != req)
					validPart2 += 1;
		}
		// check for single occurance of req in second index
		else if (max < pass.size()) {
			if (pass[max] == req)
				validPart2 += 1;
		}

	}

	f.close();

	std::cout << "Number of valid passwords part 1: " << validPart1 << std::endl;
	std::cout << "Number of valid passwords part 2: " << validPart2 << std::endl;
	return 0;

}