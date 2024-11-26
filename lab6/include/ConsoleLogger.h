#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "Observer.h"
#include <iostream>

class ConsoleLogger : public Observer {
public:
    void logEvent(const std::string &event) override {
        std::cout << event << std::endl;
    }
};

#endif
