#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <memory>
#include <map>
#include <algorithm>

#include "score.h"
using namespace std;

map<char, int> sscheme(const string &ssf) {
    ifstream fs (ssf);
    char c; 
    int k;
    map<char, int> out;
    while (fs >> c) {
        if (fs >> k) {
            out.emplace(c,k);
        } else {
            cerr << "Error: Key/Value Pair Formatting Incorrect" << endl;
        }
    }
    return out;
}

int score(const string &s, const map<char, int> &scheme) {
    int out = 0;
    for (auto q : s) {
        if(scheme.find(q) != scheme.end()) {
            out += scheme.find(q)->second;
        }
    }
    return out;
}

void score(const string &fname, const string &ofname, const map<char, int> &scheme) {
    ifstream fs (fname);
    ofstream out (ofname);
    string s;
    while (true) {
        getline(fs, s);
        if(fs.eof()) {break;}
        out << '"' << s << "\"," << score(s, scheme) << endl;
    }
}