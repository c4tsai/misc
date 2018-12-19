#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>

#include "dictionary.h"
using namespace std;

Dictionary::Dictionary(): keys{vector<string>()}, upstream{vector<vector<string>>()},
    downstream{vector<vector<string>>()} {}

int Dictionary::read(const string key) const {
    for (unsigned int i = 0; i < keys.size(); ++i) {
        if (keys[i] == key) {
            return i;
    }}
    return -1;
}
    
void Dictionary::add(const pair<string, string> &pr) {
    string fst = pr.first, snd = pr.second;
    bool flag = false;
  for (unsigned int i = 0; i < keys.size(); ++i) {
    if (keys[i] == fst) {
      downstream[i].emplace_back(snd); 
      flag = true;
    }
  }
  if (!flag) {
    keys.emplace_back(fst);
    upstream.emplace_back(vector<string>());
    downstream.emplace_back(vector<string>{snd});
  }
  flag = false;
  for (unsigned int i = 0; i < keys.size(); ++i) {
    if (keys[i] == snd) {
      upstream[i].emplace_back(fst); 
      flag = true;
    }
  }
  if (!flag) {
    keys.emplace_back(snd);
    upstream.emplace_back(vector<string>{fst});
    downstream.emplace_back(vector<string>());
  }
  return;
}

void Dictionary::del(const string &key) {
  for (unsigned int i = 0; i < keys.size(); ++i) {
    if (keys[i] == key) {
        for_each (downstream[i].begin(), downstream[i].end(), [&] (string s) {
            int ind = read(s), tmp;
            for (unsigned int j = 0; j < upstream[ind].size(); ++j) {
                if (upstream[ind].at(j) == s) {
                    tmp = j;
                }
            }
            upstream[ind].erase(upstream[ind].begin()+tmp);
        });
        keys.erase(keys.begin()+i);
        upstream.erase(upstream.begin()+i);
        downstream.erase(downstream.begin()+i);
    }
  }
}

int Dictionary::size() const {
    return keys.size();
}

vector<string> Dictionary::get_top_lvl() const {
    vector<string> out {};
    for (unsigned int i = 0; i < keys.size(); ++i) {
        if (upstream[i].size() == 0) {
            out.emplace_back(keys.at(i));
        }
    }
    sort(out.begin(), out.end());
    return out;
}