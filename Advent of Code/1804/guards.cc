#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>

#include "guards.h"
using namespace std;

Date::Date(int y, int m, int d, int h, int min): year{y}, month{m}, day{d}, hour{h}, min{min} {}
    
Date::~Date() {}

int Date::getMin() const {
    return min;
}

bool operator<(const Date &ths, const Date &oth) {
    vector<int> t1 {ths.year, ths.month, ths.day, ths.hour, ths.min};
    vector<int> t2 {oth.year, oth.month, oth.day, oth.hour, oth.min};
    bool out = true;
    bool flag = false;
    for (int i = 0; i < 5; i++) {
        if (t1.at(i) < t2.at(i)) {
            flag = true;
            break;
        }
        if (t1.at(i) > t2.at(i)) {
            flag = true;
            out = false;
            break;
        }
    }
    if (!flag) {cerr << "Warning: Two times are equal" << endl;}
    return out; 
}

bool operator>(const Date &ths, const Date &oth) {
    return !(ths < oth);
}

int operator-(const Date &ths, const Date &oth) {
    bool negative = false;
    if (ths.year < oth.year || ths.month < oth.month || ths.day < oth.day) {
        negative = true;
    }
    int m1 = ths.hour*60 + ths.min;
    int m2 = oth.hour*60 + oth.min;
    int ans = m1 - m2;
    if (negative) {ans += 24*60;}
    return ans;
}

Guard::Guard(int id): id{id}, sleep{vector<int>(61,0)} {}

Guard::~Guard() {}

void Guard::addsleep(const Date &start, const Date &wake) {
    int tb = start.getMin();
    int tf = wake.getMin();
    transform(sleep.begin() + tb, sleep.begin() + tf, sleep.begin() + tb, [=](int i) {return ++i;});
}

int Guard::total_sleep() const {
    int out = 0;
    for (auto q : sleep) {
        out += q;
    }
    return out;
}

int Guard::get_most_asleep() const {
    int ans =-1;
    int n = 0;
    for (int i = 0; i < 61; i++) {
        if (sleep.at(i) > n) {
            n = sleep.at(i);
            ans = i;
        }
    }
    return ans;
}

int Guard::get_id() const {
    return id;
}

Event::Event(int type, int id, const Date &date): type{type}, id{id}, time{date} {}

Event::~Event() {}

bool operator<(const Event &ths, const Event &oth) {
    return (ths.time < oth.time);
}

int str2int(const string &str) {
    stringstream ss(str);
    int q; 
    if(!(ss >> q)) {throw (2);}
    return q;
}

vector<Event> parse(const string &fname) {
    vector<Event> out {};
    ifstream fs (fname);
    string s;
    while(getline(fs,s)) {
        stringstream ss {s};
        getline(ss, s, '-');
        s.erase(s.begin());
        int y = str2int(s);
        getline(ss, s, '-');
        int m = str2int(s);
        ss >> s; 
        int d = str2int(s);
        getline(ss, s, ':');
        int h = str2int(s);
        getline(ss, s, ']');
        int min = str2int(s);
        Date date = Date(y,m,d,h,min);
        ss >> s;
        if (s == "wakes") {
            out.emplace_back(Event(2,0,date));
        } else if (s == "falls") {
            out.emplace_back(Event(1,0,date));
        } else {
            ss >> s; s.erase(s.begin());
            out.emplace_back(Event(0, str2int(s), date));
        }
    }
    sort(out.begin(), out.end());
    return out;
}

vector<Guard> make_guardlist(const vector<Event> &events) {
    vector<Guard> out;
    Guard* gp = nullptr;
    Date stime(0,0,0,0,0); 
    for (auto q : events) {
        if (q.type == 0) {
            gp = nullptr;
            for (unsigned int i = 0; i < out.size(); i++) {
                if (out.at(i).get_id() == q.id) {
                    gp = &(out.at(i));
                    break;
                }
            }
            if (gp == nullptr) {
                out.emplace_back(Guard(q.id));
                gp = &(out.back());
            }
        } else if (q.type == 1) {
            stime = q.time;
        } else if (q.type == 2) {
            gp->addsleep(stime, q.time);
            cout << *gp << endl;
        }
    }
    return out;
}

pair<int, int> findmax(const vector<Guard> &glist) {
    int id, max = -1;
    for (auto q : glist) {
        if (q.total_sleep() > max) {
            max = q.total_sleep();
            id = q.get_id();
        }
    }
    return pair<int, int>(id, max);
}

ostream& operator<<(ostream &os, const Date &date) {
    os << date.year << "/" << date.month << "/" << date.day << " " << date.hour << ":" << date.min;
    return os;
}

ostream& operator<<(ostream &os, const Event &event) {
    os << "Type: " << event.type;
    if (event.type == 0) {os << ", ID: " << event.id;}
    os << " [" << event.time << "]";
    return os;
}

ostream& operator<<(ostream &os, const Guard &guard) {
    os << "ID #" << guard.id << " : ";
    for (auto q : guard.sleep) {
        os << char('0' + q);
    }
    return os;
}