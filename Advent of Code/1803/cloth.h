#ifndef __CLOTH_H__
#define __CLOTH_H__

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "cells.h"

struct Listing {
    int id;
    int x;
    int y;
    int l;
    int h;
};

std::ostream& operator<<(std::ostream &out, const Listing &l);

int str2int(const std::string &str);

std::unique_ptr<std::vector<Listing>> parse(const std::string &fname);

class Job final : public PT {
    Job(const Listing &lst);
    ~Job();
    bool is_conflict(const Board &b) const;
};

std::unique_ptr<std::vector<Job>> make_jobs(std::vector<Listing> &lst, Board &board);

int count_conflicts(const Board &b);

int first_no_conflict(const std::vector<Job> &jlst,const Board &board);

#endif