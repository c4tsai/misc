#ifndef __COINPART__
#define __COINPART__

#include <vector>

class GF {
    int maxind;
    std::vector<int> fn;
  public: 
    GF(int maxN, int n1);
    void addkind(int k);
    int getN() const;
    void printall() const;
};

int coinpart(const int &maxN, const std::string &fname);

#endif
