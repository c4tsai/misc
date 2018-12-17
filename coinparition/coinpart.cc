#include <iostream> 
#include <fstream> 
#include <string>
#include <sstream>

#include "coinpart.h"
using namespace std;

GF::GF(int maxN, int n1): maxind{maxN+1}, fn{vector<int>(maxind, 0)} {
    for(int i = 0; i < maxind; i += n1) {
        fn.at(i) = 1;
    }
}

void GF::addkind(int k) {
  for(int i = 1; i < maxind; i++) {
    int head = maxind - i;
    for (int j = 1; j < head; j++) {
	  int curr = head - j*k;
	  if (curr >= 0) {
	    fn.at(head) += fn.at(curr);
	  }
        }
    }
}

int GF::getN() const {
    return fn.at(maxind - 1);
}

void GF::printall() const {
  int i = 0;
  for (auto n:fn) {
    cout << i << ": " << n << endl;
    i++;
  }
}

int coinpart(const int &maxN, const std::string &fname) {
    ifstream fs (fname);
    int q;
    if(!(fs >> q)) throw 2;
    GF model (maxN, q);
    string s;
    while(fs >> s) {
        istringstream iss {s}; 
        if (iss >> q) {model.addkind(q);} 
        else {cerr << "Expected int from file: received '" << s << "' (skipped)" << endl;}
    }
    // model.printall();
    return model.getN();
}
