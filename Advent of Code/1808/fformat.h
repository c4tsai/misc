#ifndef __FFORMAT_H__
#define __FFORMAT_H__

#include <vector>
#include <string>
#include <memory>
#include <queue>

class Treenode {
    std::vector<Treenode*> children;
    std::vector<int> metadata;
    int numchildren;
    int nummetadata;
    
  public:
    Treenode(std::queue<int> &inputs);
    ~Treenode();
    
    int getmetadata() const;
    int summetadata();
};

std::queue<int> parse(const std::string &fname);

#endif