#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

int calculateTrees(char map[][31], int x_down, int y_down, int x, int y) {
    int o_count = 0;
    int x_count = 0;
    
    int c_x = 0;
    int c_y = 0;


    while (c_y < y) {
        if (map[c_y][c_x] == '.') {
            o_count++;
        }
        else if (map[c_y][c_x] == '#') {
            x_count++;
        }

        c_x += x_down;
        c_y += y_down;

        if (c_x >= x) {
            int prev = c_x - x_down;
            int fill = x - prev;
            c_x = x_down - fill;
        }
    }
    return x_count;
}

int main() {
    const int x = 31;
    const int y = 323;
    char map[y][x];

    ifstream InputFile("data.txt");

    string curr;
    int j = 0;
    while (getline(InputFile, curr)) {
        for (int i = 0; i < curr.size(); ++i) { 
            map[j][i] = curr[i];
        }
        ++j;
    }

    // Verify that map data has been loaded in
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            cout << map[i][j];
        }
        cout << '\n';
    }

    // Part 1
    cout << "Trees 1: " << calculateTrees(map, 3, 1, 31, 323) << endl;

    //Part 2
    vector<pair<int, int>> tests = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
    long total = 1;
    for (int i = 0; i < tests.size(); ++i) {
        total *= calculateTrees(map, tests[i].first, tests[i].second, 31, 323);
    }

    cout << "Trees 2: " << total << endl;
    return 0;
}