#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "Observer.h"
#include <fstream>

class FileLogger : public Observer {
private:
    std::ofstream file;

public:
    FileLogger(const std::string &filename) : file(filename, std::ios::app) {
        if (!file.is_open()) throw std::runtime_error("Failed to open log file");
    }

    void logEvent(const std::string &event) override {
        file << event << std::endl;
    }
};

#endif