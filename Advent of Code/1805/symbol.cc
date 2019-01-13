#include <map>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "symbol.h"
using namespace std;

map<string, string> sscheme(const string &ssf) {
    ifstream fs (ssf); 
    string k, c;
    map<string, string> out;
    while (fs >> k) {
        fs >> c;
        out.emplace(k,c); 
    }
    return out;
}

vector<string> pReduce(const string &fname, const map<string, string> &ssch) {
    ifstream fs (fname);
    vector<string> out;
    char w;
    string prev = "";
    while (fs >> w) {
        string r;
        r.push_back(w);
        string q {ssch.find(r)->second};
        if(q == prev) {
            out.pop_back();
            if (out.empty()) {
                prev = "";
            } else {
                prev = out.back();
            }
        } else {
            out.emplace_back(r);
            prev = r;
        }
    }
    return out;
}

vector<string> pReduceR(const string &fname, const map<string, string> &ssch, const string &f) {
    ifstream fs (fname);
    vector<string> out;
    char w;
    string prev = "";
    while (fs >> w) {
        string r;
        r.push_back(w);
        string q {ssch.find(r)->second};
        if ((f == r) || (f == q)) {
        } else if(q == prev) {
            out.pop_back();
            if (out.empty()) {
                prev = "";
            } else {
                prev = out.back();
            }
        } else {
            out.emplace_back(r);
            prev = r;
        }
    }
    return out;
}