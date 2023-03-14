#include <iostream>
#include "LineCounter.h"

int main(int argc, char* argv[]) {


    std::string path = ".\\testData";
    if(argc==2){
        path = argv[1];
    }
    std::cout <<path<< std::endl;
    LineCounter lc = LineCounter();
    lc.startCounting(path);
    std::cout <<lc.getTotalLines()<< std::endl;
    return 0;
}
