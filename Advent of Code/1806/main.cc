#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <utility>

#include "cells.h"

int main(int argc, char* argv[]) {
    std::stringstream ss;
    std::string fname = "input.txt";
    bool p1 = true;
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
	if (s == "-p") {
	  p1 = false;
	}
    }
    
    int ans;
    
    try {
        std::unique_ptr<Board> board = std::make_unique<Board> (10000,10000);
        auto lst = parse(fname);
        std::unique_ptr<std::vector<Job>> jobs = make_jobs(*lst, *board);
	if (p1) {
        ans = count_conflicts(*board);
        std::cout << "Total: " << ans << std::endl;
	} else {
	  for (auto q : *jobs) {
	    bool temp = q.is_conflict(*board);
	    if (!temp) {
	      std::cout << "No Conflicts: " << q.get_id() << std::endl;
	    }
	  }
	}
    }	
    catch(int e) {
        switch(e) {
            case 2 : {
                std::cerr << "Passed file contains unexpected input: expecting int" << std::endl;
                return 2;
            }
            case 3 : {
                std::cerr << "Number out of bounds" << std::endl;
                return 3;
            }
        }
    }
    
    /*
    ans = first_no_conflict(fname);
    std::cout << "First Conflictless: " << ans << std::endl;
    */
    
    return 0;
}
