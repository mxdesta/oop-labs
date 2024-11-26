#ifndef DRAGON_H
#define DRAGON_H

#include "NPC.h"

class Dragon : public NPC {
public:
    Dragon(std::string name, int x, int y) : NPC(std::move(name), x, y) {}

    std::string getType() const override { return "Dragon"; }

    bool fight(NPC &opponent) override;
};

#endif