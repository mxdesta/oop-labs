#ifndef NPC_H
#define NPC_H

#include <string>
#include <cmath>

class NPC {
protected:
    std::string name;
    int x, y;

public:
    NPC(std::string name, int x, int y) : name(std::move(name)), x(x), y(y) {}
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;

    const std::string &getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }

    double distanceTo(const NPC &other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    virtual bool fight(NPC &opponent) = 0;
};

#endif
