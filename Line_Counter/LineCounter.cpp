//
// Created by IT on 2023-03-14.
//

#include <filesystem>
#include <fstream>
#include "LineCounter.h"

LineCounter::LineCounter() : pool(std::thread::hardware_concurrency()), totalLines(0) {

}

LineCounter::~LineCounter() {

}

void LineCounter::startCounting(std::string path) {

    process_directory(path);
    pool.wait_all();
}
 void LineCounter::count_lines(std::string path) {
    std::ifstream file;
    file.open(path);
    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        count++;
    }
    file.close();

     std::unique_lock<std::mutex> lock(mtx);
//    mtx.lock();
//    std::cout<<"id "<<std::this_thread::get_id()<<std::endl;
    totalLines += count;
//    mtx.unlock();
}

void LineCounter::process_directory(std::string path) {
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string filePath = entry.path().string();
        if (entry.is_directory()) {
            pool.enqueue([this, filePath] { process_directory(filePath); });
        } else {
            pool.enqueue([this, filePath] { count_lines(filePath); });
        }

    }
}

unsigned int LineCounter::getTotalLines() const {
    return totalLines;
}

