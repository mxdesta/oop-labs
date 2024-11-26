#ifndef WANDERINGKNIGHT_H
#define WANDERINGKNIGHT_H

#include "NPC.h"

class WanderingKnight : public NPC {
public:
    WanderingKnight(std::string name, int x, int y) : NPC(std::move(name), x, y) {}

    std::string getType() const override { return "WanderingKnight"; }

    bool fight(NPC &opponent) override;
};

#endif
