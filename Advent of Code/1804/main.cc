#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <memory>

#include "guards.h"

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
    int id, max;
    
    std::cout << "Parsing File" << std::endl;
    std::unique_ptr<std::vector<Event>> events = std::make_unique<std::vector<Event>>(parse(fname));
    
    /*
    for(auto q : *events) {
        std::cout << q << std::endl;
    } */
    
    std::cout << "Making Guard List" << std::endl;
    std::unique_ptr<std::vector<Guard>> glist = std::make_unique<std::vector<Guard>>(make_guardlist(*events));
    
    std::cout << "Finding Max Total Sleep" << std::endl;
    std::pair<int, int> result = findmax(*glist);
    
    id = result.first;
    
    for(auto q : *glist) {
        if (q.get_id() == id) {
            max = q.get_most_asleep();
            std::cout << q << std::endl;
        }
    }
    
    std::cout << id << " * " << max << " = " << id*max << std::endl;
    
    return 0;
}
