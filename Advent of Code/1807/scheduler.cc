#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>

#include "dictionary.h"
#include "scheduler.h"
using namespace std;

unique_ptr<vector<pair<string, string>>> parse(const string fname) {
    ifstream fs (fname);
    unique_ptr<vector<pair<string, string>>> out = make_unique<vector<pair<string, string>>>();
    string s, s1 = "", s2 = "";
    while (getline(fs, s)) {
        s1 = "";
        s2 = "";
        istringstream iss {s};
        while(s1 == "") {
            getline(iss, s, ' ');
            if (s.length() == 1) {
                s1 = s;
            }
        };
        while(s2 == "") {
            getline(iss, s, ' ');
            if (s.length() == 1) {
                s2 = s;
            }
        };
        out->emplace_back(pair<string,string>(s1, s2));
    }
    return out;
}

unique_ptr<Dictionary> make_dictionary(const vector<pair<string, string>> &words) {
    unique_ptr<Dictionary> dict = make_unique<Dictionary>();
    for (auto w : words) {
        dict->add(w);
    }
    return dict;
}

unique_ptr<vector<string>> get_order(Dictionary dict) {
    unique_ptr<vector<string>> out = make_unique<vector<string>>();
    string s;
    while (dict.size() > 0) {
        s = dict.get_top_lvl().front();
        out->emplace_back(s);
        dict.del(s);
    }
    return out;
}