//
// Created by IT on 2023-03-14.
//

#ifndef LINE_COUNTER_LINECOUNTER_H
#define LINE_COUNTER_LINECOUNTER_H


#include "ThreadPool.h"

class LineCounter {
public:
    LineCounter();
    virtual ~LineCounter();
    void startCounting(std::string path);
    unsigned int getTotalLines() const;

private:
    ThreadPool pool;
    unsigned int totalLines=0;
    std::mutex mtx;

    void count_lines(std::string path);
    void process_directory(std::string path);


};


#endif //LINE_COUNTER_LINECOUNTER_H
