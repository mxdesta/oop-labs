#ifndef ELF_H
#define ELF_H

#include "NPC.h"

class Elf : public NPC {
public:
    Elf(std::string name, int x, int y) : NPC(std::move(name), x, y) {}

    std::string getType() const override { return "Elf"; }

    bool fight(NPC &opponent) override;
};

#endif