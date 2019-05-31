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
        cout << "Numchildren: " << numchildren;
        nummetadata = inputs.front();
        inputs.pop();
        cout << "; Nummetadata: " << nummetadata << endl;
        while (children.size() < numchildren) {
            children.push_back(new Treenode(inputs));
        }
        cout << "# of children added: " << children.size() << endl;
        cout << "Adding Metadata: ";
        while (metadata.size() < nummetadata) {
            metadata.emplace_back(inputs.front());
            cout << metadata.back() << " ";
            inputs.pop();
        }
        cout << endl;
}

Treenode::~Treenode() {
    for (auto x : children) {
        delete x;
    }
}

// May have to write copy constructors

int Treenode::getmetadata() const {
    cout << "Nummetadata: " << nummetadata << endl;
    int out = 0;
    if (nummetadata > 0) {
        for (auto x : metadata) {
            cout << x << endl;
            out += x;
        }
    } 
    return out;
}

int Treenode::summetadata() {
    int out = getmetadata();
    if (numchildren > 0) {
        for (auto x : children) {
            cout << "Entering subtree" << endl;
            if (x != nullptr) {
                int tmp = x->summetadata();
                cout << tmp << endl;
                out += tmp;
            }
        }
    }
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

