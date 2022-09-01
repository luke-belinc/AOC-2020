//
//  main.cpp
//  day3
//
//  Created by Luke Belinc on 12/25/20.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int calc_trees(std::vector<std::vector<char> >&, int, int);

int main(void) {
    
    // open input data file
    std::fstream f ("input.txt", std::ios::in);
    
    if (!f.is_open()) {
        std::cout << "\nError opening input.txt\n";
        return -1;
    }

    // grid matrix
    std::vector<std::vector<char> > grid;

    // read data into grid matrix
    std::string line;
    while (std::getline(f, line)) {
        std::vector<char> temp(line.begin(), line.end());
        grid.push_back(temp);
    }
    
    // set up arrays of slopes, total trees variable
    int slopes[][2] = {{1,1}, {1,3}, {1,5}, {1,7}, {2,1}};
    int total_trees = 0;
    
    // total number after multiplying all of total trees
    // initialized at 1 to use *= operator
    unsigned long total_mult = 1;

    // loop over slopes and call calc_trees with slopes
    for (int i = 0; i < 5; i++) {
        total_trees = calc_trees(grid, slopes[i][0], slopes[i][1]);
        std::cout << "\n Right: " << slopes[i][0] 
                  << ", Down: " << slopes[i][1]
                  << ", Total trees: " << total_trees
                  << std::endl;
        
        // update total_mult
        total_mult *= total_trees; 
    }

    // output total_mult
    std::cout << "\nTotal after multiplying tree totals together: " << total_mult << std::endl;

    f.close();
    
}


int calc_trees(std::vector<std::vector<char> >& grid, int down, int right) {
    int tree_count = 0;
    
    // first coord: (1, 3) ;; right 3, down 1
    // i represents x
    // j represents y
    int j = 0;
    for (int i = 0; i < grid.size(); i+=down) {
        // simulate repeated lines by using modulus operation
        if (grid[i][j % grid[i].size()] == '#') tree_count++;
        // increment run by 3
        j += right;
    }

    return tree_count;

} 
