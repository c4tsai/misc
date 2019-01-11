#ifndef __SCORE_H__
#define __SCORE_H__

#include <iostream>
#include <string>
#include <map>

std::map<char, int> sscheme(const std::string &ssf);

int score(const std::string &s, const std::map<char, int> &scheme);

void score(const std::string &fname, const std::string &ofname, const std::map<char, int> &scheme);

#endif