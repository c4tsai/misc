#include <iostream> 
#include <fstream> 
#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "total.h"
#include "bst.h"
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

int first_duplicate(const string &fname) {
    auto nums = parse(fname);
    int n = 0;
    vector<int> dups;
    BST sums(n);
    while(dups.empty()) {
        for (auto i : *nums) {
            n += i;
            if (sums.in_tree(n)) {dups.emplace_back(n);}
            else {sums.add_to_tree(n);}
        }
    }
    return dups[0];
}