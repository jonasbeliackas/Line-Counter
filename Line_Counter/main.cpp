#include <iostream>
#include "LineCounter.h"

int main(int argc, char* argv[]) {

    LineCounter lc = LineCounter();
    std::string path = ".\\testData";
    lc.startCounting(path);
    std::cout <<lc.getTotalLines()<< std::endl;
    return 0;
}
