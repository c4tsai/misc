#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <string>
#include <map> 
#include <utility>
#include <vector>

std::map<std::string, std::string> sscheme(const std::string &ssf);

std::vector<std::string> pReduce(const std::string &fname, const std::map<std::string, std::string> &ssch);

std::vector<std::string> pReduceR(const std::string &fname, const std::map<std::string, std::string> &ssch, const std::string &r);


#endif 