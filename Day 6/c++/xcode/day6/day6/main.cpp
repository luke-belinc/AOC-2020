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

int main(int argc, char **argv) {
    
    /*
    if (argc < 2) {
        std::cout << "Please provide input" << std::endl;
        return -1;
    }
    */
    
    std::fstream fs("~/OneDrive - Wayne State University/projects/advent of code/6/input.txt", std::ios::in);
    if (!fs.is_open()) {
        std::cout << "Error opening " << "input.txt" << std::endl;
        return -2;
    }

    unsigned int total_answered = 0;
    unsigned int total_unanimous = 0;

    std::vector<std::string> groups;

    std::string line;
    std::string yes_answers = "";
    while(std::getline(fs, line)) {
        
        if (line.length() < 1 || fs.eof()) {
            if (groups.size() == 1) total_unanimous += groups[0].length();
            else {
                for (auto c : groups[0]) {
                    int total = 0;
                    for (auto str : groups) {
                        if (str.find(c) != std::string::npos) ++total;
                    }
                    if (total == groups.size()) ++total_unanimous;
                }
            }

            groups.clear();
            yes_answers = "";
        }
        else {
            for (auto c : line)
                if (yes_answers.find(c) == std::string::npos) {
                    yes_answers += c;
                    total_answered++;
                }

            groups.push_back(line);
        }
    }


    std::cout << "total answered yes: " << total_answered << std::endl;
    std::cout << "total unanimous yes: " << total_unanimous << std::endl;
    
    std::cout << "Expected: 35\n";
    fs.close();
    
    return 0;
}

