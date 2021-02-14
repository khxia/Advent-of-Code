#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set> 
#include <algorithm>

using namespace std;

int main() {
    string myText;
    ifstream MyReadFile("data.txt");
    int curr;
    unordered_set<int> mp;
    vector<int> all_nums;
    while(getline(MyReadFile, myText)) {
        curr = stoi(myText);
        all_nums.push_back(curr);
    }
    sort(all_nums.begin(), all_nums.end());
    int target = 2020;
    for (int i = 0; i < all_nums.size(); ++i) {

        // Two Sum: problem 1
        int num = all_nums[i];
        int complement = target - num;
        if (mp.find(complement) != mp.end()) {
            cout << num << " " << complement << endl;
        }
        if (mp.find(num) == mp.end()) {
            mp.insert(num);
        }

        // Three Sum: problem 2
        int targ2 = target - all_nums[i];
        int k = all_nums.size() - 1;
        int j = i+1;
        while (j < k) {
            if (all_nums[j] + all_nums[k] < targ2) {
                j++;
            } 
            else if (all_nums[j] + all_nums[k] > targ2) {
                k--;
            }
            else {
                cout << all_nums[i] << " " << all_nums[j] << " " << all_nums[k] << endl;
                j++;
                k--;
            }
        }
        
    }
    return 0;
}