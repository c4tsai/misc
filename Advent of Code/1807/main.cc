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
    bool speed = false;
    unsigned int numelves = 5;
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
            speed = true;
        }
        if (s == "-e") {
            if (i + 1 < argc) {
                s = argv[i+1];
                unsigned int q;
                std::istringstream iss (s);
                if (iss >> q) {
                    numelves = q;
                } else {
                    std::cerr << "Flag -e is not followed by unsigned integer number of elves" << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "Flag -e is not followed by unsigned integer number of elves" << std::endl;
                return 1;
            }
            i++;
        }
    }
    
    std::unique_ptr<Dictionary> dict = make_dictionary(*parse(fname));
    std::vector<std::string> tmp = *(get_order(*dict));
    for (auto q : tmp) {
        std::cout << q;
    }
    std::cout << std::endl;
    
    std::pair<std::string, int> result = elves(*dict, numelves, speed);
    std::cout << "Order: " << result.first << "; Time Taken: " << result.second << std::endl;
    
    return 0;
}
