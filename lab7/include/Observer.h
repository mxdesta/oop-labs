#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual void logEvent(const std::string& event) = 0;
    virtual ~Observer() = default;
};

#endif