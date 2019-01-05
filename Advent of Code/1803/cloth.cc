#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <fstream>
#include <sstream>

#include "cloth.h"
using namespace std;

ostream& operator<<(ostream &out, const Listing &l) {
    out << "(ID# " << l.id << "): (x,y) = (" << l.x << ", " << l.y << "); (l, h) = (" 
        << l.l << ", " << l.h << ")" << endl;
    return out;
}

int str2int(const string &str) {
    stringstream ss(str);
    int q; 
    if(!(ss >> q)) {throw (2);}
    return q;
}

unique_ptr<vector<Listing>> parse(const string &fname) {
    vector<Listing> out {};
    ifstream fs (fname);
    string s;
    while(getline(fs,s)) {
        Listing lst;
        stringstream ss (s);
        ss >> s; s.erase(s.begin());
        lst.id = str2int(s);
        ss >> s; getline(ss, s, ',');
        lst.x = str2int(s);
        getline(ss, s, ':');
        lst.y = str2int(s);
        getline(ss, s, 'x');
        lst.l = str2int(s);
        getline(ss, s);
        lst.h = str2int(s);
        out.emplace_back(lst);
    }
    unique_ptr<vector<Listing>> p = make_unique<vector<Listing>> (out);
    return p;
}

Job::Job(const Listing &lst) {
    (*this).id = lst.id;
    vector<pair<int, int>> tmp {};
    for (int i = 0; i < lst.l; i++) {
        for(int j = 0; j < lst.h; j++) {
            tmp.emplace_back(pair<int, int>(lst.x + i, lst.y + j));
        }
    }
    (*this).cells = move(tmp);
}

Job::~Job() {}

bool Job::is_conflict(const Board &b) const {
    bool flag = false;
    for (auto i : cells) {
        if(b.get_cell(i)->count_claims() > 1) {
            flag = true; break;
        }
    }
    return flag;
}

unique_ptr<vector<Job>> make_jobs(vector<Listing> &lst, Board &board) {
    unique_ptr<vector<Job>> out = make_unique<vector<Job>> ();
    for (auto q : lst) {
        Job j = Job(q);
        for (auto c : j.get_cells()) {
            board.get_cell(c)->add_id(j.get_id());
        }
        out->emplace_back(j);
    }
    return out;
}

int count_conflicts(const Board&b) {
    int len = b.get_dims().first;
    int hgt = b.get_dims().second;
    int out = 0;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < hgt; j++) {
            if (b.get_cell(i+1,j+1)->count_claims() > 1) {out++;}
        }
    }
    return out;
}
}