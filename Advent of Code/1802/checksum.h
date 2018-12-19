#ifndef __CHECKSUM_H__
#define __CHECKSUM_H__

#include <string>
#include <memory>
#include <vector>
#include <utility>

std::unique_ptr<std::vector<std::string>> parse(const std::string fname); 

int count_instance(const std::string str, int times);

int checksum(const std::string fname);

int hamming(const std::string s1, const std::string s2);

std::pair<std::string, std::string> find_last_hamming_dist(const std::vector<std::string> &words, int dist);

std::string del_diff(std::pair<std::string, std::string> pr);

#endif