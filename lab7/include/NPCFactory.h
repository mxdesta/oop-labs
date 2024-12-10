#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include "WanderingKnight.h"
#include "Elf.h"
#include "Dragon.h"
#include <memory>

class NPCFactory {
public:
    static std::unique_ptr<NPC> createNPC(const std::string &type, const std::string &name, int x, int y);
};

#endif
