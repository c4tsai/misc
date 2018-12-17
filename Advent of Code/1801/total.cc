#include <iostream> 
#include <fstream> 
#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "total.h"
using namespace std;

unique_ptr<vector<int>> parse(const string &fname){
    ifstream fs (fname);
    unique_ptr<vector<int>> out = make_unique<vector<int>>();
    string s;
    int i;
    while (fs >> s) {
        if (s[0] == '+') {s.erase(0,1);}
        istringstream iss (s);
        if (iss >> i) {
            out->emplace_back(i);
        }
    }
    return out;
}

int total(unique_ptr<vector<int>> pv) {
    int n = 0;
    for (auto i : *pv) {
        n += i;
    }
    return n;
}

int total(const string &fname) {
    return total(parse(fname));
}
