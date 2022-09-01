#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <map>

typedef unsigned long long ull_t;

ull_t calc_total_paths(std::map<size_t, std::vector<size_t> >&, const size_t&, std::map<size_t, ull_t>&);

int main() {
    std::ifstream file_in("input.txt", std::ios::in);

    if (!file_in.is_open()) {
        std::cout << "\nError opening input...\n";
        return -1;
    }

    // input set, used in part 1
    std::set<size_t> sInput;

    // get input
    std::string line;
    while (std::getline(file_in, line)) {
        try {
            // convert strings to ints
            const size_t val = std::stoi(line);
            sInput.insert(val);
        }
        catch (...) {
            std::cout << "\nCould not convert " << line << " to int...\n";
        }
    }

    //
    // ================= PART 1 ==================
    //
    int dif_three = 0;
    int dif_one = 0;
    int prev = 0;

    for (const auto& n : sInput) {
        if (n - prev == 1) dif_one++;
        else dif_three++;
        prev = n;
    }
    
    // get my adapters jolts
    int my_adapter_jolts = prev + 3;
    dif_three++;

    // output part 1
    std::cout << "\n3 and 1 jolt differences multiplied: " << dif_one * dif_three << std::endl;

    //
    // ================= PART 2 ==================
    //
    
    // directed acyclic graph map
    std::map<size_t, std::vector<size_t> > mDAG;
    // memoization map
    std::map<size_t, ull_t> mMem;

    // fill mDAG
    size_t start = 0;
    auto it_start = sInput.begin();
    do {

        for (auto pos = it_start; pos != sInput.end(); ++pos) {
            if (*pos - start > 3) break;
            else mDAG[start].push_back(*pos);
        }

        start = *it_start;
        ++it_start;

    } while (it_start != sInput.end());

    // update mDAG with jolts for my adapter
    it_start--;
    mDAG[*it_start].push_back(my_adapter_jolts);

    // uncomment to print out mDAG
    //std::cout << "\nDAG Map\n";
    //for (const auto& pair : mDAG) {
    //    std::cout << pair.first << " -> { ";
    //    for (const auto& n : pair.second) {
    //        std::cout << n << " ";
    //    }
    //    std::cout << "}\n";
    //}

    // count total number of paths in mDAG to determine total combinations
    // using memoization method
    // mMem[0] will contain total number of paths
    std::cout << "\nTotal number of combinations: " << calc_total_paths(mDAG, 0, mMem) << "\n";

    file_in.close();
    return 0;
}

// function to calculate the total number of paths in the DAG
// uses a lambda as a helper at line 119
ull_t calc_total_paths(std::map<size_t, std::vector<size_t> >& mDAG, const size_t& start, std::map<size_t, ull_t>& mMem) {

    // return mMem[start] if we have already counted subsequent number of paths starting from start
    if (mMem.find(start) != mMem.end()) {
        return mMem[start];
    }
    // begin counting paths starting at mDAG[start] as long as mDAG[start].size() > 0
    else if (mDAG[start].size()) {
        // start summing number of paths using lambda that
        //  1. iterates over mDAG[start] vector
        //  2. recursively calls calc_total_paths internally
        mMem[start] = 
            ([&mDAG, &mMem](const size_t& s) -> ull_t {
                ull_t sum = 0;
                for (const auto& x : mDAG[s])
                    sum += calc_total_paths(mDAG, x, mMem);
                return sum;
            })(start);

        // return current total
        return mMem[start];
    }
    // if we reach the end of a path, return 1
    // this should be reached after passing mDAG[last_node][0] into calc_total_paths
    else {
        return 1;
    }
}