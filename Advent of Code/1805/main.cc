#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <memory>
#include <map>
#include <vector>

#include "symbol.h"

int main(int argc, char* argv[]) {
    std::stringstream ss;
    std::string fname = "input.txt";
    std::string ssf = "alpha.txt";
    for (int i = 1; i < argc; i++) {
        std::string s = argv[i]; 
        if (s == "-f") {
            if (i + 1 < argc) {
                s = argv[i+1];
                std::ifstream fs (s);
                if (fs.is_open()) {
                    fname = s;
                } else {
                    std::cerr << "Unable to open file" << std::endl;
                    return 2;
                }
            } else {
                std::cerr << "Flag -f is not followed by file name" << std::endl;
                return 1;
            }
            i++;
        }
        if (s == "-s") {
            if (i + 1 < argc) {
                s = argv[i+1];
                std::ifstream fs (s);
                if (fs.is_open()) {
                    ssf = s;
                } else {
                    std::cerr << "Unable to open file" << std::endl;
                    return 2;
                }
            } else {
                std::cerr << "Flag -s is not followed by file name" << std::endl;
                return 1;
            }
            i++;
        }
    }
    auto ssch = std::make_unique<std::map<std::string, std::string>>(sscheme(ssf));
    std::vector<std::string> rpoly = pReduce(fname, *ssch);
    
    std::cout << rpoly.size() << std::endl;
    
    for (int i = 0; i < 26; i++) {
        std::string q;
        q.push_back('A' + i);
        std::vector<std::string> rpoly2 = pReduceR(fname, *ssch, q);
        std::cout << q << ": " << rpoly2.size() << std::endl;
    }
    
    return 0;
}
