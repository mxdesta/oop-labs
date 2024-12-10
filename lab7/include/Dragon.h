#ifndef DRAGON_H
#define DRAGON_H

#include "NPC.h"
#include <string>

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y);

    std::string getType() const override;        // Совпадает с NPC::getType()
    int getMovementDistance() const override;   // Совпадает с NPC::getMovementDistance()
    int getKillingRange() const override;       // Совпадает с NPC::getKillingRange()
    bool fight(NPC& opponent) override;         // Совпадает с NPC::fight()
};

#endif
