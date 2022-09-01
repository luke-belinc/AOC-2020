// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    vector<string> input{
        "10 10",
        "< a value = \"GoodVal\" >",
        "<b value = \"BadVal\" size = \"10\">",
        "< / b>",
        "<c height = \"auto\">",
        "<d size = \"3\">",
        "<e strength = \"2\">",
        "< / e>",
        "< / d>",
        "< / c>",
        "< / a>",
        "a~value",
        "b~value",
        "a.b~size",
        "a.b~value",
        "a.b.c~height",
        "a.c~height",
        "a.d.e~strength",
        "a.c.d.e~strength",
        "d~sze",
        "a.c.d~size"
    };

    int n_lines = 0,
        n_queries = 0;

    /*
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }
    */

    int pos = input.at(0).find_first_of(" ");
    n_lines = stoi(input.at(0).substr(0, pos));
    n_queries = stoi(input.at(0).substr(pos+1));

    map<string, vector<string>> tags;

    string ignore = "/ <>=";

    for (int i = 1; i < n_lines; ++i) {

        if (input[i].find('/') != string::npos) continue;

        size_t pos = input[i].find_first_of(' ');
        if (pos == 1) pos = input[i].find(' ', pos+1);
        string tag = input[i].substr(1, pos - 1);

        for (const auto& c : ignore) {
            tag.erase(remove(tag.begin(), tag.end(), c), tag.end());
        }

        vector <string> subtags = ([&]() {
                
            int line = i+1;
            string subtag;
            vector<string> temp;

            while (line < n_lines) {

                if (input[line].find('/') != string::npos) {
                    if (input[line].find(tag) != string::npos) {
                        break;
                    }
                }
                else {
                    size_t pos = input[line].find(' ');
                    if (pos == 1) pos = input[line].find(' ', pos + 1);

                    subtag = input[line].substr(1, pos - 1);

                    for (const auto& c : ignore) {
                        subtag.erase(remove(subtag.begin(), subtag.end(), c), subtag.end());
                    }

                    temp.push_back(subtag);
                }
                
                line++;
            }

            return temp;
        })();

        tags.insert(make_pair(tag, subtags));

    }


    for (const auto& p : tags) {
        cout << p.first << " : ";
        for (const auto& t : p.second) {
            cout << t << "";
        }
        cout << endl;
    }

    /*for (int i = n_lines + 1; i < n_lines + n_queries + 1; ++i) {
        vector<string> tokens;

        size_t pos1 = 0;
        size_t pos2 = input[i].find('.');

        while (pos2 != string::npos) {
            tokens.push_back(input[i].substr(pos1, pos2 - pos1));
            pos1 = pos2 + 1;
            pos2 = input[i].find('.', pos2 + 1);
        }

        pos2 = input[i].find('~');
        tokens.push_back(input[i].substr(pos1, pos2 - pos1));

        string attr = input[i].substr(pos2 + 1);

        int j = 0;
        for (int k = 1; k < n_lines + 1; ++k) {
            if (input[k].find(tokens[j]) != string::npos) {
                if (input[k].find('/') == string::npos) {
                    if (j == tokens.size() - 1) {
                        if (input[k].find(attr) != string::npos) {
                            pos1 = input[k].find('"');
                            pos2 = input[k].find('"', pos1 + 1);
                            cout << input[k].substr(pos1 + 1, pos2 - pos1 - 1) << endl;
                            j = 0;
                            break;
                        }
                    }
                    else {
                        ++j;
                    }
                }
                else {
                    cout << "Not found!" << endl;
                    j = 0;
                    break;
                }
            }
        }
    }*/

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
