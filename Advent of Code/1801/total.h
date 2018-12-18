#ifndef __TOTAL_H__
#define __TOTAL_H__

#include <vector>
#include <memory>

std::unique_ptr<std::vector<int>> parse(const std::string &fname);
int total(std::unique_ptr<std::vector<int>> pv);
int total(const std::string &fname);

int first_duplicate(const std::string &fname);

#endif