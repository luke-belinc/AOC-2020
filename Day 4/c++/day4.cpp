//
//
// Author: Luke Belinc
// 
// ADVENT OF CODE
// Day 4: Passport Processing
//
//

#include <cstdio>
#include <cstdint>
#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <regex>

int main(void) {

    // bit masks 
    constexpr std::uint_fast8_t byr { 0b1000'0000 }; // birthyear
    constexpr std::uint_fast8_t iyr { 0b0100'0000 }; // issue year
    constexpr std::uint_fast8_t eyr { 0b0010'0000 }; // expiration year
    constexpr std::uint_fast8_t hgt { 0b0001'0000 }; // height
    constexpr std::uint_fast8_t hcl { 0b0000'1000 }; // hair color
    constexpr std::uint_fast8_t ecl { 0b0000'0100 }; // eye color
    constexpr std::uint_fast8_t pid { 0b0000'0010 }; // passport id

    // regex masks
    std::regex byr_r ("19[0-9][0-9]|20[0-1][0-9]|2020");
    std::regex iyr_r ("201[0-9]|2020");
    std::regex eyr_r ("202[0-9]|2030");
    std::regex hgt_r ("[0-9]+cm|[0-9]+in");
    std::regex hcl_r ("#[0-9a-f]{6}");
    std::regex ecl_r ("[a-z]{3}");
    std::regex pid_r ("[0-9]{8,}");

    // open file stream
    std::fstream f("input.txt", std::ios::in);
    if (!f.is_open()) {
        std::cout << "\nError opening input.txt\n";
        f.close();
        return -1;
    }
    
    std::vector<std::map<std::string, std::string> > passport_data;
    std::string line;
    
    std::map<std::string, std::string> temp_map;

    while (std::getline(f, line)) {

        if (line.length() < 1) {

            if (temp_map.size() > 0) { 
                passport_data.push_back(temp_map);
            }
            
            temp_map.clear();
        }

        else {

            std::stringstream sstr(line);
            std::string token;
            while (std::getline(sstr, token, ' ')) {
                if (token.length() > 1) {
                    std::string field = token.substr(0, 3);
                    std::string data = token.substr(4, token.length());
                    temp_map.insert(std::pair<std::string, std::string>(field, data));
                }
            }
        }
    }

    int num_valid = 0;
    for (auto const& m : passport_data) {

        std::uint_fast8_t flags { 0b0000'0001 };
        
        if (m.find("byr") != m.end()) if (std::regex_match(m.at("byr"), byr_r)) flags |= byr;
        if (m.find("iyr") != m.end()) if (std::regex_match(m.at("iyr"), iyr_r)) flags |= iyr;
        if (m.find("eyr") != m.end()) if (std::regex_match(m.at("eyr"), eyr_r)) flags |= eyr;
        if (m.find("hgt") != m.end()) if (std::regex_match(m.at("hgt"), hgt_r)) flags |= hgt;
        if (m.find("hcl") != m.end()) if (std::regex_match(m.at("hcl"), hcl_r)) flags |= hcl;
        if (m.find("ecl") != m.end()) if (std::regex_match(m.at("ecl"), ecl_r)) flags |= ecl;
        if (m.find("pid") != m.end()) if (std::regex_match(m.at("pid"), pid_r)) flags |= pid;
    
        if (flags == (std::uint_fast8_t){ 0b1111'1111 }) num_valid++;
    }
    
    std::cout << "\nTotal number of entries: " << passport_data.size();
    std::cout << "\nTotal number of valid passports: " << num_valid << std::endl;


    // close file stream and exit program
    f.close();
    return 0;
}
