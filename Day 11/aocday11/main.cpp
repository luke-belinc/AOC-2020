#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <map>

int main() {
    std::ifstream file_in("input.txt", std::ios::in);

    if (!file_in.is_open()) {
        std::cout << "\nError opening input...\n";
        return -1;
    }

    std::vector<std::string> inputsVector;
    std::vector<std::vector<int>> seating;

    // get input
    std::string line;
    while (std::getline(file_in, line)) {
        std::vector<int> temp;
        for (auto const& c : line) {
            if (c == 'L') temp.push_back(0);
            else temp.push_back(-1);
        }
        inputsVector.push_back(line);
        seating.push_back(temp);
    }

    std::vector<std::string> updatedVector(inputsVector);
    do {

        inputsVector = updatedVector;
        updatedVector.clear();

        /*
        left  = [row][col - 1]
        right = [row][col + 1]

        down = [row + 1][col]
        up   = [row - 1][col]

        up_left    = [row - 1][col - 1]
        up_right   = [row - 1][col + 1]

        down_left  = [row + 1][col - 1]
        down_right = [row + 1][col + 1]
        
        */

        for (int row = 0; row < inputsVector.size(); ++row) {

            std::string temp = "";
            for (int col = 0; col < inputsVector[row].length(); ++col) {

                if (inputsVector[row][col] == '.') {
                    temp += '.';
                    continue;
                }

                int numOccupied = 0;
          
                if (col > 0 && col < inputsVector[row].length() - 1) {
                    // left
                    if (inputsVector[row][col - 1] == '#') ++numOccupied;
                    // right
                    if (inputsVector[row][col + 1] == '#') ++numOccupied;

                    if (row > 0) {
                        // up
                        if (inputsVector[row - 1][col] == '#') ++numOccupied;
                        // up_left
                        if (inputsVector[row - 1][col - 1] == '#') ++numOccupied;
                        // up_right
                        if (inputsVector[row - 1][col + 1] == '#') ++numOccupied;
                    }
                    if (row < inputsVector.size() - 1) {
                        // down
                        if (inputsVector[row + 1][col] == '#') ++numOccupied;
                        // down_left
                        if (inputsVector[row + 1][col - 1] == '#') ++numOccupied;
                        // down_right
                        if (inputsVector[row + 1][col + 1] == '#') ++numOccupied;
                    }
                }
                else if (col == 0 && row > 0 && row < inputsVector.size() - 1) {
                    // up
                    if (inputsVector[row - 1][col] == '#') ++numOccupied;
                    // up_right
                    if (inputsVector[row - 1][col + 1] == '#') ++numOccupied;
                    // right
                    if (inputsVector[row][col + 1] == '#') ++numOccupied;
                    // down_right
                    if (inputsVector[row + 1][col + 1] == '#') ++numOccupied;
                    // down
                    if (inputsVector[row + 1][col] == '#') ++numOccupied;
                }
                else if (col == inputsVector[row].length() - 1 && row > 0 && row < inputsVector.size() - 1) {
                    // up
                    if (inputsVector[row - 1][col] == '#') ++numOccupied;
                    // up_left
                    if (inputsVector[row - 1][col - 1] == '#') ++numOccupied;
                    // left
                    if (inputsVector[row][col - 1] == '#') ++numOccupied;
                    // down_left
                    if (inputsVector[row + 1][col - 1] == '#') ++numOccupied;
                    // down
                    if (inputsVector[row + 1][col] == '#') ++numOccupied;
                }

                if (inputsVector[row][col] == 'L') temp += (numOccupied == 0) ? '#' : 'L';
                else if (inputsVector[row][col] == '#') temp += (numOccupied >= 4) ? 'L' : '#';
            }

            updatedVector.push_back(temp);
        }
    } while (inputsVector != updatedVector);
    
    int count = 0;
    for (auto const& s : updatedVector) {
        for (auto const& c : s) {
            if (c == '#') ++count;
        }
        std::cout << s << std::endl;
    }

    std::cout << "Total occupied seats: " << count << std::endl;
    return 0;
}