#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    ifstream DataFile("data.txt");
    string curr;

    regex r1("(hgt|ecl|pid|iyr|byr|hcl|eyr|cid):[a-zA-Z0-9#]+");
    int valid_count = 0;
    bool new_passport = false;
    vector<int> attributes = {0 , 0, 0, 0, 0, 0, 0, 0};
    bool invalid_format = false;
    while (getline(DataFile, curr)) {
        if (curr.size() == 1) {
            // check valid
            for (int i = 0; i < attributes.size(); ++i) {
                if ((i != 7 && attributes[i] == 0) || invalid_format ) {
                    valid_count--;
                    break;
                }
            }
            valid_count++;
            new_passport = true;
            continue;
        }
        if (new_passport) {
            for (int i = 0; i < attributes.size(); ++i) {
                attributes[i] = 0;
            }
            new_passport = false;
            invalid_format = false;
        }
        smatch m;
        while(regex_search(curr, m, r1) && !invalid_format) {
            string x = m.str();
            string s = x.substr(0, 3);
            string v = x.substr(4, x.size()-4);
            if (s == "hgt") {
                attributes[0] = 1;
                string c_or_i = v.substr(v.size()-2, 2);
                int num;
                try {
                    num = stoi(v.substr(0, v.size()-2));
                } catch(const std::invalid_argument& e) {
                    invalid_format = true;
                    num = 0;
                    continue;
                }
                if (c_or_i == "cm") {
                    if (num < 150 || num > 193) {
                        invalid_format = true;
                    }
                }
                else if (c_or_i == "in") {
                    if (num < 59 || num > 76) {
                        invalid_format = true;
                    }
                }
                else {
                    invalid_format = true;
                }
            }
            else if (s == "ecl") {
                attributes[1] = 1;
                string clr = v.substr(0, 3);
                if (!(clr == "amb" || clr == "blu" || clr == "brn" || clr == "gry" || clr == "grn" || clr == "hzl" || clr == "oth")) {
                    invalid_format = true;
                }
            }
            else if (s == "pid") {
                attributes[2] = 1;
                int sze = 0;
                for (auto &c: v) {
                    if (!isdigit(c) || sze > 8) {
                        invalid_format = true;
                    }
                    sze++;
                }
            }
            else if (s == "iyr") {
                attributes[3] = 1;
                string yr_str = v.substr(0,4);
                int yr;
                try {
                    yr = stoi(yr_str);
                } catch (const int& e) {
                    yr = 0;
                    invalid_format = true;
                    continue;
                }
                if (yr < 2010 || yr > 2020) {
                    invalid_format = true;
                }
            }
            else if (s == "byr") {
                attributes[4] = 1;
                string yr_str = v.substr(0,4);
                int yr;
                try {
                    yr = stoi(yr_str);
                } catch (const int& e) {
                    yr = 0;
                    invalid_format = true;
                    continue;
                }
                if (yr < 1920 || yr > 2002) {
                    invalid_format = true;
                }
            }
            else if (s == "hcl") {
                attributes[5] = 1;
                if (v[0] != '#') {
                    invalid_format = true;
                }
                string dgts = v.substr(1, 7);
                if (dgts.size() != 6)
                    invalid_format = true;
                for (auto &c: dgts) {
                    if (!(isdigit(c) || (c >= 97 && c <= 102))) {
                        invalid_format = true;
                    }
                }
            }
            else if (s == "eyr") {
                attributes[6] = 1;
                string yr_str = v.substr(0,4);
                int yr;
                try {
                    yr = stoi(yr_str);
                } catch (const int& e) {
                    yr = 0;
                    invalid_format = true;
                    continue;
                }
                if (yr < 2020 || yr > 2030) {
                    invalid_format = true;
                }
            }
            else if (s == "cid") {
                attributes[7] = 1;
            }
            else {
                std::cout << s << endl;
            }
            curr = m.suffix();
        }
    }
    // for (int i = 0; i < attributes.size(); ++i) {
    //     if (i != 7 && attributes[i] == 0) {
    //         valid_count--;
    //         break;
    //     }
    // }
    // valid_count++;
    std::cout << valid_count << endl;
    return 0;
}