#include "../include/Elf.h"

bool Elf::fight(NPC &opponent) {
    return opponent.getType() == "WanderingKnight";
}