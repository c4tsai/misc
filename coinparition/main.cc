#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <utility>

#include "coinpart.h"

int main(int argc, char* argv[]) {
  using namespace std;
    int maxN = 100;
    
    std::stringstream ss;
    std::string fname = "coins.txt";
    int tmpint;
    for (int i = 1; i < argc; i++) {
        std::string s = argv[i]; 
        if (s == "-n") { // For setting N
            if (i + 1 < argc) {
                s = argv[i+1];
                ss.str(s);
                if (ss >> tmpint) {
                    maxN = tmpint; 
                } else {
                    std::cerr << "Flag -n is not followed by integer" << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "Flag -n is not followed by integer" << std::endl;
                return 1;
            }
            i++;
        }
        if (s == "-p") {
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
                std::cerr << "Flag -p is not followed by file name" << std::endl;
                return 1;
            }
            i++;
        }
    }
    int ans;
    try {
    ans = coinpart(maxN, fname);
    }
    catch(...) {
        std::cerr << "Passed file contains unexpected input: expecting int" << std::endl;
        return 2;
    }
    std::cout << ans << std::endl;
    return 0;
}
