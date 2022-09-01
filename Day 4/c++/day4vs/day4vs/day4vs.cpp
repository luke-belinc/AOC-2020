//
// 
// ADVENT OF CODE
// Day 4: Passport Processing
//
//

#include <cstdint>   // std::uint_fast8_t
#include <iostream>  // std::cout, std::cin, std::endl
#include <string>    // std::string, std::getline
#include <map>       // std::map, std::pair
#include <fstream>   // std:fstream
#include <sstream>   // std::stringstream
#include <regex>     // std::regex, std::regex_match

int main(void) {

    // regex masks
    std::regex byr_r("19[2-9][0-9]|200[0-2]");
    std::regex iyr_r("201[0-9]|2020");
    std::regex eyr_r("202[0-9]|2030");
    std::regex hgt_r("((1[5678][0-9])|(19[0-3]))cm|(59|6[0-9]|7[0-6])in");
    std::regex hcl_r("#([a-f0-9]){6}");
    std::regex ecl_r("amb|blu|brn|gry|grn|hzl|oth");
    std::regex pid_r("[0-9]{9}");
    
    // map to bit masks and regex masks
    std::map<std::string, std::pair<std::regex, std::uint_fast8_t> > masks {
        {"byr", { byr_r, 0b1000'0000 }}, // birthyear
        {"iyr", { iyr_r, 0b0100'0000 }}, // issue year
        {"eyr", { eyr_r, 0b0010'0000 }}, // expiration year
        {"hgt", { hgt_r, 0b0001'0000 }}, // height
        {"hcl", { hcl_r, 0b0000'1000 }}, // hair color
        {"ecl", { ecl_r, 0b0000'0100 }}, // eye color
        {"pid", { pid_r, 0b0000'0010 }}  // passport id
    };

    // open file stream
    std::fstream fs("input.txt", std::ios::in);
    if (!fs.is_open()) {
        std::cout << "\nError opening input.txt\n";
        fs.close();
        return -1;
    }
    
    std::string line;

    // keep track of flags
    std::uint_fast8_t flags1{ 0b0000'0001 };
    std::uint_fast8_t flags2{ 0b0000'0001 };
    
    unsigned int num_valid1 = 0;
    unsigned int num_valid2 = 0;
    unsigned int num_total = 0;

    // read in lines from input.txt
    while (std::getline(fs, line)) {

        std::stringstream sstr(line);
        std::string token;

        // parse field and data
        while (std::getline(sstr, token, ' ')) {
            if (token.length() > 1) {

                std::string field = token.substr(0, 3);
                std::string data = token.substr(4, token.length());

                auto const& it = masks.find(field);

                if (it != masks.end()) {
                    // PART 1
                    flags1 |= it->second.second;
                    // PART 2
                    if (std::regex_match(data, it->second.first))
                        flags2 |= it->second.second;
                }
            }
        }

        if (line.length() < 1 || fs.eof()) {
            num_total++;

            if (flags1 == 0b1111'1111) num_valid1++;
            if (flags2 == 0b1111'1111) num_valid2++;

            flags1 = flags2 = 0b0000'0001;
        }
    }

    std::cout << "\nTotal number of entries: " << num_total;
    std::cout << "\nTotal number of valid passports (part 1): " << num_valid1;
    std::cout << "\nTotal number of valid passports (part 2): " << num_valid2 << std::endl;

    // close file stream and exit program
    fs.close();
    return 0;
}
