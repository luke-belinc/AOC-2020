//
//
// Advent of Code: Day 7
// By Luke Belinc
//
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

unsigned int count_total_parents(
	std::unordered_map<std::string, std::vector<std::pair<std::size_t, std::string> > >& types_map,
	std::string bag_type,
	std::vector<std::string>& found
);

unsigned int count_total_children(
	std::unordered_map<std::string, std::vector<std::pair<std::size_t, std::string> > >& types_map,
	std::string bag_type
);

int main(void) {

	// open input
	std::ifstream fs("input.txt");

	// map to store bag parent types corresponding child types
	std::unordered_map<std::string, std::vector<std::pair<std::size_t, std::string> > > types_map;

	// parse input
	std::string line;
	while (std::getline(fs, line)) {

		// get parent bag type
		std::size_t pos = line.find(" bags contain");
		std::string parent_type = line.substr(0, pos);

		// get child bag types
		std::stringstream child_types(line.substr(pos + 13));
		std::vector<std::pair<std::size_t, std::string> > temp_vector;
		while (std::getline(child_types, line, ',')) {

			// strip unecessary text
			pos = line.find(" bag");
			std::string child_type = (line[0] == ' ') ? line.substr(1, pos - 1) : line.substr(0, pos - 1);

			try {
				// convert number from string to int
				std::size_t count = (child_type[0] != 'n') ? std::stoi(child_type.substr(0, 1)) : 0;

				// add pair to temporary pairs vector
				if (count > 0) temp_vector.push_back(std::make_pair(count, child_type.substr(2)));
				else temp_vector.push_back(std::make_pair(count, ""));
			}
			catch (...) {
				std::cout << "Error string: " << child_type << std::endl;
			}
		}

		// make pair of child bag types and parent bag type and store in map
		types_map.insert(std::make_pair(parent_type, temp_vector));

	}

	// declare found vector for count_total_parents
	std::vector<std::string> found;
	
	// my bag type
	std::string my_bag_type = "shiny gold";

	// part 1
	unsigned int count1 = count_total_parents(types_map, my_bag_type, found);
	// part 2
	unsigned int count2 = count_total_children(types_map, my_bag_type);

	// output
	std::cout << "\n(part 1) " << count1 << " total bags that could carry a shiny gold bag"
		      << "\n(part 2) " << count2 << " total bags included with a shiny gold bag\n";

	// close file
	fs.close();

	return 0;
}

// part 1, count the number of total individual bags that could carry at least one of my bags
unsigned int count_total_parents(
	std::unordered_map<std::string, std::vector<std::pair<std::size_t, std::string> > >& types_map,
	std::string bag_type,
	std::vector<std::string>& found
) {

	unsigned int count = 0;

	for (auto const& map_entry : types_map) {
		for (auto const& pair : map_entry.second) {
			if (pair.second == bag_type) {
				if (std::find(found.begin(), found.end(), map_entry.first) == found.end()) {
					found.push_back(map_entry.first);
					count += (1 + count_total_parents(types_map, map_entry.first, found));
				}
			}
		}
	}

	return count;
}

// part 2, count total number of bags included with my bag
unsigned int count_total_children(
	std::unordered_map<std::string, std::vector<std::pair<std::size_t, std::string> > >& types_map,
	std::string bag_type
) {

	unsigned int count = 0;

	std::unordered_map<std::string, std::vector<std::pair<std::size_t, std::string> > >::const_iterator start_iterator = types_map.find(bag_type);

	if (start_iterator != types_map.end()) {
		for (auto const& pair : (*start_iterator).second) {
			if (pair.first > 0) {
				count += (pair.first + (pair.first * count_total_children(types_map, pair.second)));
			}
		}
	}

	return count;
}