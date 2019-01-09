#ifndef __GUARDS_H__
#define __GUARDS_H__

#include <string>
#include <vector>
#include <utility>
#include <iostream>

class Date {
    int year;
    int month;
    int day;
    int hour;
    int min;
    
  public: 
    Date(int y, int m, int d, int h, int min);
    ~Date();
    int getMin() const;
    
    friend bool operator<(const Date &ths, const Date &oth); // technically <=
    friend bool operator>(const Date &ths, const Date &oth);
    friend int operator-(const Date &ths, const Date &oth);
    friend std::ostream& operator<<(std::ostream &os, const Date &date);
};

class Guard {
    int id;
    std::vector<int> sleep;
    
  public:
    Guard(int id);
    ~Guard();
    void addsleep(const Date &start, const Date &wake);
    int total_sleep() const;
    std::pair<int,int> get_most_asleep() const;
    int get_id() const;
    friend std::ostream& operator<<(std::ostream &os, const Guard &guard);
};

struct Event {
    int type;
    int id;
    Date time;
    
    Event(int type, int id, const Date &date);
    ~Event();
    friend bool operator<(const Event &ths, const Event &oth);
    friend std::ostream& operator<<(std::ostream &os, const Event &event);
};

int str2int(const std::string &str);

std::vector<Event> parse(const std::string &fname);

std::vector<Guard> make_guardlist(const std::vector<Event> &events);

std::pair<int, int> findmax(const std::vector<Guard> &glist);

std::pair<int, int> findmaxasleepmin(const std::vector<Guard> &glist);

#endif