#include <algorithm>
#include <string> 
#include <fstream> 
#include <memory>
#include <vector>
#include <iostream>
#include <utility>

#include "checksum.h"
using namespace std;

unique_ptr<vector<string>> parse(const string fname) {
    ifstream fs (fname);
    unique_ptr<vector<string>> out = make_unique<vector<string>>();
    string s;
    while (fs >> s) {
        out->emplace_back(s);
    }
    return out;
}

int count_instance(const string str, int times) {
    string s = str;
    sort(s.begin(), s.end());
    int i = -1, out = 0;
    char c = '\a';
    for (auto q : s) {
        if (c == q) {
            i++;
        } else {
            if (i == times) {out++;}
            c = q;
            i = 1;
        }
    }
    if (i == times) {out++;}
    return out;
}


int checksum(const std::string fname) {
    auto in = parse(fname);
    unique_ptr<vector<bool>> dblvec = make_unique<vector<bool>>(); 
    unique_ptr<vector<bool>> tripvec = make_unique<vector<bool>>();
    for_each(in->begin(), in->end(), [&] (string s) {
        if (count_instance(s, 2) > 0) {
            dblvec->emplace_back(true);
        } else {
            dblvec->emplace_back(false);
        }
        if (count_instance(s, 3) > 0) {
            tripvec->emplace_back(true);
        } else {
            tripvec->emplace_back(false);
        }
    });
    int d, t;
    d = count_if(dblvec->begin(), dblvec->end(), [&] (bool b) {return b;});
    t = count_if(tripvec->begin(), tripvec->end(), [&] (bool b) {return b;});
    return d*t;
}

int hamming(const std::string s1, const std::string s2) {
    unsigned int l = s1.length(), out = 0;
    if (l != s2.length()) {
        cerr << "Hamming Distance is not defined for strings of different lengths" << endl;
        throw 20;
    }
    for (unsigned int i = 0; i < l; i++) {
        if (s1.at(i) != s2.at(i)) {out++;}
    }
    return out;
}

pair<string, string> find_last_hamming_dist(const vector<string> &words, int dist) {
    string out1 = "", out2 = "";
    for(unsigned int i = 0; i < words.size(); i++) {
        string s1 = words.at(i);
        for_each(words.begin() + i + 1, words.end(), [&] (string s2) {
            if (hamming(s1, s2) == dist) {
                out1 = s1; out2 = s2;
            }
        });
    }
    return pair<string, string>(out1, out2);
}

string del_diff(pair<string, string> pr) {
    string out = "", s1 = pr.first, s2 = pr.second;
    for (unsigned int i = 0; i < s1.length(); i++) {
        if(s1.at(i) == s2.at(i)) {
            out.push_back(s1.at(i));
        }
    }
    return out;
}