#include "../include/Elf.h"

bool Elf::fight(NPC &opponent) {
    // Реализация функции
    return this->getKillingRange() > opponent.getKillingRange();
}
