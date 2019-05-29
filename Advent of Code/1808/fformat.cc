#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>

#include "fformat.h"
using namespace std;

Treenode::Treenode(queue<int> *inputs): children{vector<unique_ptr<Treenode>>()}, 
    metadata{vector<int>()}, numchildren{0}, nummetadata{0} {
        numchildren = *inputs.front();
        *inputs.pop();
        nummetadata = *inputs.front();
        *inputs.pop();
        while (children.size() < numberchildren) {
            children.push_back(make_unique<Treenode>(inputs));
        }
        while (metadata.size() < nummetadata) {
            metadata.emplace_back(*inputs.front();
            *inputs.pop();
        }
}

Treenode::~Treenode() {}

vector<int> Treenode::getmetadata() const {
    return metadata;
}

int Treenode::summetadata() {
    vector<int> temp{};
    temp.emplace_back(getmetadata());
    for (auto x : children) {
        temp.emplace_back(x->summetadata());
    }
    int out = accumulate(temp.begin(), temp.end(), 0);
}

queue<int> parse(const string &fname) {
    queue<int> out {};
    int tmp;
    ifstream fs (fname);
    while (fs >> tmp) {
        out.emplace(tmp);
    }
    return out;
}

