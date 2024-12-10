#include "../include/NPCFactory.h"
#include <stdexcept>

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string &type, const std::string &name, int x, int y) {
    if (type == "WanderingKnight")
        return std::make_unique<WanderingKnight>(name, x, y);
    if (type == "Elf")
        return std::make_unique<Elf>(name, x, y);
    if (type == "Dragon")
        return std::make_unique<Dragon>(name, x, y);
    throw std::invalid_argument("Unknown NPC type");
}