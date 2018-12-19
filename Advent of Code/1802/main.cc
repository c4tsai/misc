#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <utility>

#include "checksum.h"

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
    int ans;
    
    ans = checksum(fname);
    
    std::cout << "The checksum is: " << ans << std::endl;
    
    std::cout << del_diff(find_last_hamming_dist(*parse(fname), 1)) << std::endl;
    
    return 0;
}
