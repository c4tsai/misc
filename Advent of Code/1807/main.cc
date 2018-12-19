#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>

#include "scheduler.h"
#include "dictionary.h"

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
    
    Dictionary dict = *make_dictionary(*parse(fname));
    std::vector<std::string> tmp = *(get_order(dict));
    for (auto q : tmp) {
        std::cout << q;
    }
    std::cout << std::endl;
    
    return 0;
}
