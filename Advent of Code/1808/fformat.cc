#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <numeric>
#include <algorithm>

#include "fformat.h"
using namespace std;

Treenode::Treenode(queue<int> &inputs): children{vector<Treenode*>()}, 
    metadata{vector<int>()}, numchildren{0}, nummetadata{0} {
        numchildren = inputs.front();
        inputs.pop();
        nummetadata = inputs.front();
        inputs.pop();
        while (children.size() < numchildren) {
            children.push_back(new Treenode(inputs));
        }
        while (metadata.size() < nummetadata) {
            metadata.emplace_back(inputs.front());
            inputs.pop();
        }
}

Treenode::~Treenode() {
    for (auto x : children) {
        delete x;
    }
}

vector<int> Treenode::getmetadata() const {
    return metadata;
}

int Treenode::summetadata() {
    vector<int> temp = getmetadata();
    for (auto x : children) {
        temp.emplace_back(x->summetadata());
    }
    int out = accumulate(temp.begin(), temp.end(), 0);
    return out;
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

