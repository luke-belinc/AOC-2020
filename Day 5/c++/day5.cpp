//
//
// ADVENT OF CODE
// Day 5
// By Luke Belinc
//
//

#include <iostream>
#include <fstream>     // std::fstream
#include <string>      // std::string
#include <cmath>       // std::pow
#include <vector>      // std::vector
#include <algorithm>   // std::sort

int main(int argc, char **argv) {

    if (argc <= 1) { 
        std::cout << "Please provide input file" << std::endl;
        return -1;
    }

    // open file for parsing
    std::fstream fs(argv[1], std::ios::in);
    if (!fs.is_open()) { 
        std::cout << "Coult not open file: " << argv[1] << std::endl;
        return -2;
    }

    // vector for storing seat ids
    std::vector<int> seats;
    
    // max seat id for part 1 
    int seat_max = 0;

    // begin parsing input
    std::string line;
    while (std::getline(fs, line)) {
        
        int row = 0;
        for (int i = 0; i < 7; i++)
            if (line[i] == 'B') row += std::pow(2, 6-i);
        
        int col = 0;
        for (int i = 7; i < 10; i++) 
            if (line[i] == 'R') col += std::pow(2, 9-i);


        int seat = (row * 8) + col;
        seats.push_back(seat);        
        
        // part 1
        if (seat > seat_max) seat_max = seat;
    }    
    // part 1 output
    std::cout << "\nMax seat id is " << seat_max << std::endl;

    // sort seat ids for part 2
    std::sort(seats.begin(), seats.end());
    // part 2
    for (int i = 1; i < seats.size(); ++i) {
        if (seats[i + 1] - seats[i - 1] > 2) {
            std::cout << "My seat id is " << seats[i] + 1 << std::endl;
            break;
        }
    }
    
    return 0;
}
