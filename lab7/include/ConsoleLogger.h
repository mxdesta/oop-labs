#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "Observer.h"
#include <iostream>
#include <mutex>

class ConsoleLogger : public Observer {
public:
    static std::mutex cout_mutex;

    void logEvent(const std::string& event) override {
        std::lock_guard<std::mutex> guard(cout_mutex);
        std::cout << event << std::endl;
    }
};

#endif