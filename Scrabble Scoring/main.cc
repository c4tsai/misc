#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <memory>
#include <map>

#include "score.h"

int main(int argc, char* argv[]) {
    std::stringstream ss;
    std::string fname = "";
    std::string ssf = "AmE.txt";
    std::string ofname = "output.csv";
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
        if (s == "-o") {
            if (i + 1 < argc) {
                ofname = argv[i+1];
            } else {
                std::cerr << "Flag -o is not followed by file name" << std::endl;
                return 1;
            }
            i++;
        }
    }
    auto ssch = std::make_unique<std::map<char, int>>(sscheme(ssf));
    if (fname == "") {
        std::string s;
        while (std::cin >> s) {
            std::cout << score(s, *ssch) << std::endl;
        }
    } else {
        score(fname, ofname, *ssch);
    }
    return 0;
}
