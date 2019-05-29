#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <memory>
#include <vector>
#include <queue>

#include "fformat.h"

int main(int argc, char* argv[]) {
    std::stringstream ss;
    std::string fname = "input.txt";
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
    }
    auto q = std::make_unique<std::queue<int>>(parse(fname));
    auto t = std::make_unique<Treenode>(Treenode(&(*q)));
    
    int out = t->summetadata();
    
    std::cout << out << std::endl;
    
    return 0;
}