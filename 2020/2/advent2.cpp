#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

string matchRegex(string str, regex r) {
    smatch m;
    regex_search(str, m, r);
    return m.str();
}

int main() {
    int ret = 0;
    int ret2 = 0;
    string curr;
    ifstream DataFile("data.txt");

    regex r1("[0-9]+(?=-)");
    regex r2("[0-9]+(?!-) ");
    regex r3("[a-zA-Z]+(?!: )");
    regex r4("[a-z](?=: )");

    while(getline(DataFile, curr)) {
        string match1 = matchRegex(curr, r1);
        string match2 = matchRegex(curr, r2);
        string match3 = matchRegex(curr, r3);
        string match4 = matchRegex(curr, r4);
        
        
        char c = match4[0];
        int low = stoi(match1);
        int high = stoi(match2);
        int count = 0;

        bool flip = false;
        for (int i = 0; i < match3.size(); ++i) {
            if (match3[i] == c) {
                ++count;
                if (i == low - 1 || i == high - 1) {
                    flip = !flip;
                }
            }
        }

        // Part 1
        if (count >= low && count <= high) {
            ret++;
        }
        // Part 2
        if (flip) {
            ret2++;
        }
    }
    cout << "Total Count 1: " << ret << endl;
    cout << "Total Count 2: " << ret2 << endl;
    return 0;
}