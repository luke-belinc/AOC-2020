#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <set>
/*#include <chrono>*/

int main() {

    // open input file
    std::ifstream in_file("/Users/luke/OneDrive - Wayne State University/projects/advent of code/9/c++/input.txt", std::ifstream::in);
    // make sure input file was opened successfully before continuing;
    if (!in_file.is_open()) {
        std::cout << "\n\nCould not open file...\n\n";
        return -1;
    }

    // containers for elements from input and for the sums of the element
    std::vector<uint_fast64_t> data;
    std::multiset<uint_fast64_t> preamble;
    // subset of contiguous numbers that sum to the broken number in data
    // used in part 2
    std::set<uint_fast64_t> subset;

    // read in lines from input and store as numbers into data
    std::string line;
    while (getline(in_file, line)) {
        try {
            data.push_back(std::strtoull(line.c_str(), nullptr, 10));
        } catch (...) {
            std::cout << "\nCould not convert " << line << " to int...\n";
        }
    }

    /*std::chrono::high_resolution_clock::time_point start, end;*/

    // part 1
    /*start = std::chrono::high_resolution_clock::now();*/
    // initialize preamble with sums of first 25 numbers
    for (int i = 0; i < 24; ++i) {
        for (int j = i+1; j < 25; ++j) {
            preamble.insert(data[i] + data[j]);
        }
    }

    // variable to store index of broken number, used in part 2
    size_t broken_num_index = 0;
    // loop over sums checking for current number in preamble
    // while simultaneously updating preamble
    for (int i = 25; i < data.size(); ++i) {

        // check if number is in preamble sums
        if (preamble.find(data[i]) == preamble.end()) {
            broken_num_index = i;
            std::cout << data[i] << " is not a sum of the previous 25 numbers...\n";
            break;
        }

        // update preamble by erasing sums from dropped lower bound
        // and inserting new ones from increased upper bound
        for (int j = i - 24; j < i; ++j) {
            preamble.erase(preamble.find(data[i-25] + data[j]));
            preamble.insert(data[j] + data[i]);
        }
    }
    /*end = std::chrono::high_resolution_clock::now();
    std::cout << "\ntime for multiset to finish: "
              << (std::chrono::duration_cast<std::chrono::duration<double>>(end - start)).count()
              << " seconds\n\n";*/

    // part 2
    // iterator to broken number in data
    const auto& broken_num_iter = data.begin() + broken_num_index;
    // index of beginning for summing elements in data
    size_t begin = 0;
    bool found = false;
    do {

        // initialize offset
        size_t offset = 0;

        // initialize sum and store first number of sum into subset
        subset.insert(data[begin]);
        uint_fast64_t sum = data[begin++];

        // loop from beginning and add until sum is greater than or equal to broken number
        do {
            subset.insert(data[begin]);
            sum += data[begin++];
            ++offset;
        } while (sum < *broken_num_iter);

        // check to see if sum is equal to broken number
        if (sum == *broken_num_iter) {
            // update found to true to break loop
            found = true;
        } else {
            // reset begin and subset
            begin -= offset;
            subset.clear();
        }

    } while (!found && begin < broken_num_index);

    // print out numbers found
    std::cout << "\nNumbers that sum to " << *broken_num_iter << ": ";
    for (const auto& n : subset) {
        std::cout << n << " ";
    }
    std::cout << "\n\n";

    // print out sum of smallest and largest number
    // set is automatically sorted from least to greatest
    std::cout << "Sum of smallest and largest number in subset: " << *subset.begin() + *subset.rbegin();

    return 0;
}