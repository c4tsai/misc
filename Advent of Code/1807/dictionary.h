#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <vector>
#include <string>
#include <utility>

class Dictionary {
  std::vector<std::string> keys;
  std::vector<std::vector<std::string>> upstream;
  std::vector<std::vector<std::string>> downstream;
  
  int read(const std::string key) const;

 public:
  Dictionary();
  void add(const std::pair<std::string, std::string> &pr);
  void del(const std::string &key);
  std::vector<std::string> get_top_lvl() const;
  int size() const;
};

#endif
