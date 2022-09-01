//
//
// ADVENT OF CODE 2020
// Day 6
//
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {

    /*
    if (argc < 2) {
        std::cout << "Please provide input" << std::endl;
        return -1;
    }
    */

    std::fstream fs("input.txt", std::ios::in);
    if (!fs.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return -2;
    }

    unsigned int total_answered = 0;
    unsigned int total_unanimous = 0;

    std::vector<std::string> groups;
    unsigned int num_groups = 0;

    std::string yes_answers = "";
    std::string line;
    while (std::getline(fs, line)) {

        if (line.length() < 1 || fs.eof()) {

            if (num_groups == 1) total_unanimous += groups[0].length();
            else if (num_groups > 1) {
                for (auto const& c : groups[0]) {
                    int total = 1;
                    for (auto it = groups.begin() + 1; it != groups.end(); ++it) {
                        if ((*it).find(c) != std::string::npos) ++total;
                    }
                    if (total == num_groups) ++total_unanimous;
                }
            }

            groups.clear();
            num_groups = 0;
            yes_answers = "";
        }
        else {

            if (num_groups == 0) {
                total_answered += line.length();
                yes_answers = line;
            }
            else {
                for (auto c : line)
                    if (yes_answers.find(c) == std::string::npos) {
                        yes_answers += c;
                        total_answered++;
                    }
            }

            ++num_groups;
            groups.push_back(line);
        }
    }


    std::cout << "total answered yes: " << total_answered << std::endl;
    std::cout << "total unanimously answered yes: " << total_unanimous << std::endl;

    fs.close();

    return 0;
}
