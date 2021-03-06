#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <string>
#include <memory>
#include <vector>

#include "dictionary.h"

std::unique_ptr<std::vector<std::pair<std::string, std::string>>> parse(const std::string fname); 

std::unique_ptr<Dictionary> make_dictionary(const std::vector<std::pair<std::string, std::string>> &words);

std::unique_ptr<std::vector<std::string>> get_order(Dictionary dic);

int tasktime(const std::string &s, const bool speed);

std::pair<std::string, int> elves(Dictionary dic, unsigned int numelves, bool fast);

#endif