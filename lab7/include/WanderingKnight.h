#ifndef WANDERING_KNIGHT_H
#define WANDERING_KNIGHT_H

#include "NPC.h"

class WanderingKnight : public NPC {
public:
    WanderingKnight(std::string name, int x, int y)
        : NPC(std::move(name), x, y) {}

    std::string getType() const override { return "WanderingKnight"; }
    int getMovementDistance() const override { return 2; }
    int getKillingRange() const override { return 4; }

    bool fight(NPC &opponent) override; // Только объявление
};

#endif // WANDERING_KNIGHT_H
