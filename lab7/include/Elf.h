#ifndef ELF_H
#define ELF_H

#include "NPC.h"

class Elf : public NPC {
public:
    Elf(std::string name, int x, int y)
        : NPC(std::move(name), x, y) {}

    std::string getType() const override { return "Elf"; }
    int getMovementDistance() const override { return 3; }
    int getKillingRange() const override { return 5; }

    bool fight(NPC &opponent) override; // Только объявление
};

#endif // ELF_H
