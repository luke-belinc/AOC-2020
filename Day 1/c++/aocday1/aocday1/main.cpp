#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(void) {
	
	// file stream
	std::fstream f;
	f.open("input.txt", std::ios::in);

	// vector for storing numbers
	std::vector<int> nums;
	
	// get numbers from input.txt
	std::string line;
	while (getline(f, line)) {
		int num = std::stoi(line);
		nums.push_back(num);
	}

	// flag for breaking loops
	bool found = false;
	// get 2 numbers that equal to 2020
	for (int i = 0; i < nums.size(); i++) {
		for (int j = i+1; j < nums.size(); j++) {
			if (nums.at(i) + nums.at(j) == 2020) {
				std::cout << std::endl << "part 1 nums: " << nums.at(i) << ", " << nums.at(j) << std::endl;
				std::cout << "The answer to part 1: " << nums.at(i) * nums.at(j) << std::endl;
				found = true;
				break;
			}
		}
		if (found) break;
	}

	// reset flag
	found = false;
	// get 3 numbers that equal 2020
	for (int i = 0; i < nums.size(); i++) {
		for (int j = i + 1; j < nums.size(); j++) {
			for (int k = j + 1; k < nums.size(); k++) {
				if (nums.at(i) + nums.at(j) + nums.at(k) == 2020) {
					std::cout << std::endl << "part 2 nums: " << nums.at(i) << ", " << nums.at(j) << ", " << nums.at(k) << std::endl;
					std::cout << "The answer to part 2: " << nums.at(i) * nums.at(j) * nums.at(k) << std::endl;
					found = true;
					break;
				}
			}
			if (found) break;
		}
		if (found) break;
	}

	// close file stream
	f.close();

	return 0;
}