// aocday8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "hgc.h"

/*
int find_broken_line(std::vector<std::pair<int, int>>& operations);
bool find_broken_line_helper(const std::vector<std::pair<int, int>>& operations, std::set<int>& not_winning, std::set<int>& lines_visited, size_t& current_line);
*/

int main()
{
    HGC hgc;

    std::vector<std::pair<int, int>> operations;
    
    std::ifstream inf("input.txt");

    if (!inf.is_open()) {
        std::cout << "\n\nError opening file...quitting...\n";
        return -1;
    }

    std::string line;
    while (getline(inf, line)) {

        std::string operation = line.substr(0,3);
        char sign = line.substr(4,1)[0];
        
        int operand = std::stoi(line.substr(5));
        if (sign == '-') operand *= -1;

        HGC::operation op_enum{};
        int op_number = -1;
        if (operation == "acc") {
            op_enum = HGC::operation::acc;
            op_number = 0;
        }
        else if (operation == "jmp") {
            op_enum = HGC::operation::jmp;
            op_number = 1;
        }
        else if (operation == "nop") {
            op_enum = HGC::operation::nop;
            op_number = 2;
        }

        hgc.insert_op(op_enum, operand);
        
        std::pair<int, int> temp_pair(op_number, operand);
        operations.push_back(temp_pair);
    }

    int acc = 0;
    do {
        if (!hgc.check_history(hgc.get_curr_op())) {
            if (!hgc.run()) std::cout << "\n\nUnknown operation...\ncontinuing...\n";
        }
        else {
            acc = hgc.get_acc();
            break;
        }
    } while (true);

    std::cout << "\nThe value of the acc before fix is " << acc;

    int bugged_line = hgc.find_bugged_line(operations);

    if (bugged_line == operations.size()) {
        std::cout << "\n\nsomething happened...\ncouldn't find bugged line...\n\n";
    }
    else {
        std::cout << "\n\nLine causing inifinite loop: " << bugged_line;
    }

    hgc.clear_history();
    hgc.reset_acc();
    hgc.reset_curr_op();

    acc = 0;
    do {
        if (hgc.get_curr_op() != hgc.get_op_codes().end() && !hgc.check_history(hgc.get_curr_op())) {
            if (!hgc.run()) std::cout << "\n\nUnknown operation...\ncontinuing...\n";
        }
        else {
            acc = hgc.get_acc();
            break;
        }
    } while (true);

    std::cout << "\n\nThe value of the acc after fix is " << acc << "\n\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
