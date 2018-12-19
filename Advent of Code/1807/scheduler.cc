#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>
#include <algorithm>

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

unique_ptr<vector<string>> get_order(Dictionary dic) {
    Dictionary dict = dic;
    unique_ptr<vector<string>> out = make_unique<vector<string>>();
    string s;
    while (dict.size() > 0) {
        s = dict.get_top_lvl().front();
        out->emplace_back(s);
        dict.del(s);
    }
    return out;
}

int tasktime(const string &s, const bool speed) {
    char c = s[0];
    int out = c - 'A' + 1;
    if (!speed) {out += 60;}
    return out;
}

pair<string, int> elves(Dictionary dic, unsigned int numelves, bool fast) {
    Dictionary dict = dic;
    vector<pair<int, string>> time{};
    int curtime = 0;
    string s, ord = "";
    while (dict.size() > 0) {
        vector<string> task = dict.get_top_lvl();
        while(time.size() < numelves && task.size() > 0) {
            s = task.front();
            int t = tasktime(s, fast);
            bool assigned = false;
            for (auto q : time) {
                if (q.second == s) {assigned = true;}
            }
            if (!assigned) {time.emplace_back(pair<int, string>(curtime + t, s));}
            task.erase(task.begin());
        }
        sort(time.begin(), time.end(), [&] (auto i, auto j) {return (i.first < j.first);});
        auto donetask = time.front();
        curtime = donetask.first;
        ord += donetask.second;
        dict.del(donetask.second);
        time.erase(time.begin());
    }
    return pair<string, int>(ord, curtime);
}